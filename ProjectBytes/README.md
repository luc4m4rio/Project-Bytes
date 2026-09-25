# Project Bytes: networking and server structure (UE 5.8)

This project copies the way APB Reloaded splits its services. A player logs in to an **account**,
picks one of several **characters** (each has its own name, faction, rank, threat and money), then
joins a **district**. A district is a dedicated server instance such as `Financial-1` or `Waterfront-2`.
Districts can have **optional entry requirements**, for example "rank 80+ and Silver threat",
"Bronze and below", "Criminals only" or "account flag `tester`".

```
                 ┌──────────────────────── Backend (Backend/server.py) ─────────────────────────┐
  Game client ──►│ /v1/auth        accounts + sessions            ("login server")              │
  (frontend)     │ /v1/characters  N characters per account        ("character store")           │
                 │ /v1/districts   list + eligibility, join → address + signed ticket ("world")  │
                 │ /v1/servers     register / heartbeat / redeem / save progress (control plane) │◄── District servers
                 └──────────────────────────────────────────────────────────────────────────────┘     (UE dedicated,
        │                                                                                               -District=<id>)
        └──── ClientTravel  host:port?ticket=…  ──────────────────────────────────────────────────────►  PreLogin verifies
                                                                                                          ticket offline
```

## Quick start

1. **Build once.** Right-click `ProjectBytes.uproject` → *Generate Visual Studio project files*, then build
   the `Development Editor` configuration. Or run `python Tools/bytes.py build`.
2. **Run a local cluster:**

   ```bat
   Playtest up -d financial=2 -d waterfront -c 2
   ```

   (`./playtest.sh …` on Linux/macOS, or `python Tools/bytes.py …` anywhere.) This command:
   - starts the backend on `http://127.0.0.1:8080`
   - starts 2 Financial servers and 1 Waterfront server, using the engine's editor binary in `-server` mode
     on free ports from 7777 up
   - starts 2 game windows. They register and log in as `tester1`/`tester2` (password `playtest`), create
     `Tester1` (Enforcer) and `Tester2` (Criminal), and join `financial`. The backend puts both in the
     busiest instance that still has room.
   - on Ctrl+C, stops everything.

   Server logs go to `Saved/Playtest/*.log`. Run `python Tools/bytes.py status` to see instances and player counts.
3. **Play by hand.** Open the console (`~`) in a game window. A text HUD shows the account, characters,
   districts (with the reason you can't enter each locked one) and the players in your district.

   ```
   bytes.Register alice secret1        bytes.Login alice secret1
   bytes.CreateCharacter Vex Criminal  bytes.CreateCharacter Mara Enforcer
   bytes.Select Vex                    bytes.Districts
   bytes.Join financial                bytes.Join financial financial-2    (a specific instance)
   bytes.Leave                         (back to character select)
   ```

With no `-d` flags, `up` starts one server for every district in `Backend/config.json`.

### Other launcher commands

| Command | What it does |
|---|---|
| `bytes.py up [-d id[=n]]… [-c N] [-j district] [--reset]` | Starts the backend, the servers and optionally clients. `--reset` wipes the dev database first. |
| `bytes.py server financial [--port 7790]` | Adds one more instance to a running cluster. |
| `bytes.py client --user bob --faction Criminal -j breakwater` | Starts one more client. |
| `bytes.py backend [--reset]` | Runs only the backend. Useful with PIE, or when you start servers yourself. |
| `bytes.py status` | Lists registered servers and their populations. |
| `bytes.py admin list` | Lists accounts and characters. |
| `bytes.py admin set-stats Tester1 --rank 80 --threat Silver` | Sets rank/threat/money to test requirements. |
| `bytes.py admin flag tester1 tester` / `unflag` | Adds or removes an account flag. |
| `bytes.py admin slots tester1 6` | Changes an account's character slot count. |
| `bytes.py build [--target ProjectBytesEditor]` | Compiles through UnrealBuildTool. |

The launcher looks for the engine in this order: `--engine`, the `UE_ENGINE_DIR` environment variable,
`Tools/playtest.local.json` (`{"engineDir": "D:/UE_5.8"}`), then the default Epic Games Launcher path.
For packaged builds, pass `--server-exe` and `--client-exe`.

## District requirements

Requirements live in `Backend/config.json`. Every field is optional: leave it out for "no requirement".

```jsonc
{ "id": "waterfront-veteran", "displayName": "Waterfront (Veteran)", "map": "/Game/Maps/Waterfront",
  "maxPlayers": 80,
  "requirements": {
    "minRank": 80,                 // 0/absent = no minimum
    "maxRank": 0,                  // 0/absent = no maximum
    "threats": ["Silver"],         // exact list, or use a range:
    "minThreat": "Silver",         //   Green < Bronze < Silver < Gold
    "maxThreat": "Bronze",         //   e.g. maxThreat Bronze = "Bronze and below"
    "factions": ["Criminal"],      // Enforcer / Criminal
    "requiredAccountFlags": ["tester"]
  } }
```

The requirements are checked in two places:

1. **The backend**, when it lists districts and when it issues a join ticket. The client sees the
   reasons, such as `Requires rank 80 or higher (you are rank 12)`.
2. **The district server**, which receives the requirements when it registers and checks them again in
   `PreLogin` against the signed ticket. You can turn this off per game mode with
   `bEnforceRequirementsOnServer`.

The example config includes an open district (`financial`, `waterfront`), a threat cap
(`financial-bronze`), your example `waterfront-veteran` (rank 80+, Silver), a rank gate (`fightclub`),
a social district (`breakwater`) and an account-flag gate (`devtest`).

To test gating quickly, use `bytes.Dev.SetRank 80` and `bytes.Dev.SetThreat Silver` from the frontend
console (these need backend `devMode`), or `bytes.py admin set-stats`.

## How joining works

1. The client sends `POST /v1/districts/join {characterId, districtId, instanceId?}`.
2. The backend checks the requirements and picks an instance. Unredeemed tickets count as reserved
   slots, and the busiest instance with room is filled first. It then returns `address` and a
   **ticket**: `base64url(claims).base64url(HMAC-SHA1(key, claims))`. The claims carry the character
   id, name, faction, rank, threat, account flags, target server and a 60-second expiry.
3. The client runs `ClientTravel("host:port?ticket=…")`. Changing district later is the same call; the
   travel disconnects you from the old server.
4. On the server, `ABytesDistrictGameMode::PreLogin` checks the signature (the key arrives at
   registration), the expiry, that the ticket is for this server, the capacity and the requirements.
   It needs no backend round-trip.
5. `InitNewPlayer` copies the identity onto the replicated `ABytesPlayerState`. `PostLogin` then
   **redeems** the ticket once, which blocks replays, and loads the authoritative character record. If
   the backend refuses the ticket, the player is kicked.
6. The server sends a heartbeat every 5 s with the list of online characters. This drives presence and
   the population shown in the district list. Servers that stop sending heartbeats drop out after 20 s.
7. Progression goes through `AwardProgress` / `SetThreat` on the game mode, then to
   `/v1/servers/characters/update`. Rank is computed from standing (`standingPerRank`).

## Code map

| Path | Role |
|---|---|
| `Source/ProjectBytes/Public/Core/BytesTypes.h` | Shared data model: account, character, requirements, district, ticket claims, public identity. |
| `Core/BytesBackendHttp` | JSON-over-HTTP helper for backend calls. |
| `Core/BytesTicket` | Offline ticket verification (HMAC-SHA1). |
| `Core/BytesSettings` | *Project Settings → Game → Project Bytes Online*: backend URL, server key, frontend map, offline dev options. |
| `Client/BytesAccountSubsystem` | Client flow: login, characters, districts, join and travel. Blueprint-callable, handles command-line auto-login. |
| `Client/BytesConsoleCommands.cpp` | The `bytes.*` console commands. |
| `Server/BytesDistrictServerSubsystem` | Dedicated-server side: register, heartbeat, redeem, save progress. |
| `Game/BytesDistrictGameMode` | Login pipeline, requirement checks, duplicate-character handling, progression. |
| `Game/BytesPlayerState` | Replicated identity (name, faction, rank, threat, clan, appearance); money and standing replicate to the owner only. |
| `Game/BytesPlayerController` | Shows the kick reason in the frontend, plus dev cheat RPCs. |
| `Game/BytesDebugHUD` | Canvas HUD so everything can be tested with no assets (`bytes.HUD 0` hides it). |
| `Backend/server.py`, `Backend/config.json` | Backend service (Python 3.9+, standard library only, SQLite). |
| `Tools/bytes.py`, `Playtest.bat`, `playtest.sh` | Local cluster launcher. |

## Working in the editor (PIE)

A server started **without** `-District=` (PIE, or `open` on a listen server) runs *unmanaged*. It
needs no ticket and gives each player an offline dev identity: `Dev1` Enforcer, `Dev2` Criminal, and
so on. You can set that identity through URL options:
`open 127.0.0.1?BytesName=Vex?BytesFaction=Criminal?BytesRank=80?BytesThreat=Silver?BytesFlags=tester`.
To test gating in PIE, set `OfflineRequirements` in Project Settings. On your district maps, set
*World Settings → GameMode Override* to `BytesDistrictGameMode` (or a Blueprint child).
`GlobalDefaultServerGameMode` only applies to real dedicated servers.

The backend works during PIE too. Run `bytes.py backend` and use the `bytes.Login` and other console
commands in a PIE client, but tickets only matter on managed servers.

## Making it yours

- **Maps.** Every district uses `/Engine/Maps/Entry` (an empty engine map) and the default fly-around
  pawn, so the loop works before any content exists. Change `map` per district in
  `Backend/config.json`. Change `GameDefaultMap`/`FrontendMap` to your frontend map.
- **UI.** Build UMG on top of `UBytesAccountSubsystem`. Every call has a Blueprint version with a
  completion delegate, and `OnStateChanged` tells you when to refresh. Then replace `HUDClass`.
- **Character customization.** `FBytesCharacter::Appearance` is an opaque string (up to 16 KB) that is
  stored and replicated. Put your creator's serialized data there.
- **Faction spawning / loadouts.** Implement `OnCharacterEntered` in a Blueprint child of
  `BytesDistrictGameMode`.
- **More districts.** Add an entry to `config.json`. No code changes are needed.

## Going beyond local playtests

- Change `serverKey` in `Backend/config.json`, and pass the same value to servers with
  `-BytesServerKey=` or `ServerKey` in `DefaultGame.ini`. Set `devMode: false` to disable the dev
  endpoints.
- Servers on other machines need `-BytesPublicHost=<reachable ip>`. Put the backend behind TLS and
  point `-BytesBackend=` at it.
- A dedicated `ProjectBytesServer` target and a `ProjectBytesClient` target are included. Packaging
  them needs a source-built engine. The editor binary in `-server` mode (what the launcher uses) does
  not.
- The backend is deliberately small: SQLite plus one Python file. The HTTP API is the contract, so you
  can reimplement it in any stack later without touching the game code.

## Tests

```
python -m unittest discover -s Backend/tests -v
```

The tests cover accounts, character slots and name rules, requirement evaluation, instance fill,
capacity reservation, ticket signing, verification and replay rejection, heartbeat and presence,
progression, and stale-server reaping.
