// Root Cockpit - staff control panel for Project Bytes.
// Vanilla JS, no build step. Every piece of server data is rendered with textContent (player names are
// attacker-controlled), never innerHTML. The server enforces all permissions; the UI only hides what you can't do.
"use strict";

(() => {
  const TOKEN_KEY = "bytes.cockpit.token";
  const state = { token: sessionStorage.getItem(TOKEN_KEY) || "", me: null, catalog: null, view: "overview", timer: 0 };

  // ---- DOM helpers ---------------------------------------------------------------------------------

  function h(tag, attrs, ...children) {
    const el = document.createElement(tag);
    for (const [key, value] of Object.entries(attrs || {})) {
      if (value === undefined || value === null || value === false) continue;
      if (key === "class") el.className = value;
      else if (key.startsWith("on")) el.addEventListener(key.slice(2), value);
      else if (key === "value") el.value = value;
      else if (key === "checked") el.checked = !!value;
      else el.setAttribute(key, value === true ? "" : String(value));
    }
    for (const child of children.flat(Infinity)) {
      if (child === undefined || child === null || child === false) continue;
      el.append(child instanceof Node ? child : document.createTextNode(String(child)));
    }
    return el;
  }
  const $ = (sel, root = document) => root.querySelector(sel);
  const can = (perm) => !!state.me && state.me.permissions.includes(perm);
  const fmtTime = (t) => (t ? new Date(t * 1000).toLocaleString() : "-");
  const ago = (t) => {
    if (!t) return "-";
    const s = Math.max(0, Math.round(Date.now() / 1000 - t));
    return s < 60 ? `${s}s ago` : s < 3600 ? `${Math.round(s / 60)}m ago` : s < 86400 ? `${Math.round(s / 3600)}h ago` : `${Math.round(s / 86400)}d ago`;
  };
  const num = (n) => Number(n || 0).toLocaleString();
  const pill = (text, kind) => h("span", { class: `pill ${kind || ""}` }, text);

  function toast(message, isError) {
    const el = h("div", { class: `toast ${isError ? "err" : ""}` }, message);
    $("#toasts").append(el);
    setTimeout(() => el.remove(), isError ? 7000 : 4000);
  }

  function table(headers, rows, emptyText) {
    if (!rows.length) return h("div", { class: "empty" }, emptyText || "Nothing here yet.");
    return h("div", { class: "table-wrap" },
      h("table", {}, h("thead", {}, h("tr", {}, headers.map((x) => h("th", { class: x.startsWith("#") ? "num" : "" }, x.replace(/^#/, ""))))),
        h("tbody", {}, rows)));
  }

  function field(label, input) { return h("label", { class: "field" }, label, input); }

  // ---- API -----------------------------------------------------------------------------------------

  async function api(method, path, body) {
    const res = await fetch(path, {
      method,
      headers: Object.assign({ "Content-Type": "application/json" }, state.token ? { Authorization: `Bearer ${state.token}` } : {}),
      body: body ? JSON.stringify(body) : undefined,
      cache: "no-store",
    });
    let data = {};
    try { data = await res.json(); } catch (e) { /* empty */ }
    if (res.status === 401 && path !== "/admin/v1/login") {
      signOut(false);
      throw new Error(data.error || "Session expired");
    }
    if (!res.ok) {
      const reasons = (data.reasons || []).length ? `: ${data.reasons.join("; ")}` : "";
      throw new Error((data.error || `HTTP ${res.status}`) + reasons);
    }
    return data;
  }

  async function run(action, success) {
    try {
      const result = await action();
      if (success) toast(typeof success === "function" ? success(result) : success);
      return result;
    } catch (e) {
      toast(e.message, true);
      return null;
    }
  }

  // ---- Modals --------------------------------------------------------------------------------------

  // ask({title, message, danger, fields:[{name,label,type,options,value,placeholder}], confirmPhrase, wide, noReason})
  // resolves to an object of values (always including a reason unless noReason) or null if cancelled.
  function ask(opts) {
    return new Promise((resolve) => {
      const inputs = {};
      const make = (f) => {
        let input;
        if (f.type === "select") input = h("select", {}, f.options.map((o) => h("option", { value: o.value ?? o, selected: (o.value ?? o) === f.value }, o.label ?? o)));
        else if (f.type === "textarea") input = h("textarea", { placeholder: f.placeholder || "" });
        else if (f.type === "checkbox") input = h("input", { type: "checkbox", checked: f.value });
        else input = h("input", { type: f.type || "text", placeholder: f.placeholder || "", value: f.value ?? "", min: f.min, max: f.max });
        if (f.type === "textarea" && f.value) input.value = f.value;
        inputs[f.name] = input;
        return f.type === "checkbox" ? h("label", { class: "check" }, input, f.label) : field(f.label, input);
      };
      const fields = (opts.fields || []).map(make);
      if (!opts.noReason) fields.push(make({ name: "reason", label: "Reason (goes in the audit log)", placeholder: "e.g. ticket #1234, compensation for outage..." }));
      if (opts.confirmPhrase) fields.push(make({ name: "confirm", label: `Type ${opts.confirmPhrase} to confirm`, placeholder: opts.confirmPhrase }));
      const close = (value) => { backdrop.remove(); resolve(value); };
      const submit = h("button", { class: opts.danger ? "danger" : "primary", type: "submit" }, opts.okText || "Confirm");
      const form = h("form", { class: `modal ${opts.wide ? "wide" : ""}`, onsubmit: (e) => {
        e.preventDefault();
        const values = {};
        for (const [k, el] of Object.entries(inputs)) values[k] = el.type === "checkbox" ? el.checked : el.value;
        if (!opts.noReason && (values.reason || "").trim().length < 3) { inputs.reason.focus(); toast("A reason is required", true); return; }
        if (opts.confirmPhrase && values.confirm !== opts.confirmPhrase) { inputs.confirm.focus(); toast("Confirmation phrase doesn't match", true); return; }
        close(values);
      } },
        h("h2", {}, opts.title),
        opts.message ? h("p", { class: opts.danger ? "danger-note" : "muted" }, opts.message) : null,
        opts.body || null,
        fields,
        h("div", { class: "actions" }, h("button", { type: "button", class: "ghost", onclick: () => close(null) }, "Cancel"), opts.hideOk ? null : submit));
      const backdrop = h("div", { class: "modal-backdrop", onclick: (e) => { if (e.target === backdrop) close(null); } }, form);
      $("#modal-root").append(backdrop);
      const first = form.querySelector("input, select, textarea");
      if (first) first.focus();
    });
  }

  function showSecret(title, secret, uri) {
    ask({ title, noReason: true, hideOk: true, body: h("div", { class: "stack" },
      h("p", { class: "muted" }, "Shown once. Add it to an authenticator app now (Google Authenticator, 1Password, Authy...)."),
      field("Secret", h("input", { value: secret, readonly: true, class: "mono" })),
      field("otpauth URI", h("textarea", { readonly: true, class: "mono" }, uri))) });
  }

  // ---- Shell ---------------------------------------------------------------------------------------

  const VIEWS = [
    { id: "overview", label: "Overview", perm: "view", render: renderOverview, refresh: 5000 },
    { id: "deploy", label: "Deployment", perm: "view", render: renderDeploy, refresh: 4000 },
    { id: "servers", label: "Servers & Sessions", perm: "view", render: renderServers, refresh: 5000 },
    { id: "players", label: "Players", perm: "view", render: renderPlayers },
    { id: "economy", label: "Rewards & Gifts", perm: "view", render: renderEconomy },
    { id: "bans", label: "Ban Log", perm: "view", render: renderBans },
    { id: "audit", label: "Audit Log", perm: "audit.read", render: renderAudit },
    { id: "staff", label: "Staff", perm: "staff.manage", render: renderStaff },
  ];

  function signOut(callServer = true) {
    if (callServer && state.token) api("POST", "/admin/v1/logout").catch(() => {});
    state.token = "";
    state.me = null;
    sessionStorage.removeItem(TOKEN_KEY);
    clearInterval(state.timer);
    renderLogin();
  }

  function renderLogin() {
    const app = $("#app");
    app.replaceChildren();
    const user = h("input", { autocomplete: "username", required: true });
    const pass = h("input", { type: "password", autocomplete: "current-password", required: true });
    const code = h("input", { inputmode: "numeric", autocomplete: "one-time-code", maxlength: 6, placeholder: "123456" });
    const form = h("form", { onsubmit: async (e) => {
      e.preventDefault();
      const result = await run(() => api("POST", "/admin/v1/login", { username: user.value, password: pass.value, code: code.value }));
      if (!result) { pass.value = ""; code.value = ""; return; }
      state.token = result.token;
      sessionStorage.setItem(TOKEN_KEY, state.token);
      boot();
    } },
      h("div", { class: "brand" }, h("span", {}, "Project Bytes"), h("b", {}, "ROOT COCKPIT")),
      field("Staff username", user), field("Password", pass), field("Authenticator code", code),
      h("button", { class: "primary", type: "submit" }, "Sign in"),
      h("p", { class: "muted small" }, "Staff only. Every action is recorded in a tamper-evident audit log."));
    app.append(h("div", { class: "login" }, form));
    user.focus();
  }

  async function boot() {
    const me = await run(() => api("GET", "/admin/v1/me"));
    if (!me) return renderLogin();
    state.me = me.staff;
    state.catalog = await run(() => api("GET", "/admin/v1/catalog"));
    renderShell();
  }

  function renderShell() {
    const app = $("#app");
    app.replaceChildren();
    const nav = VIEWS.filter((v) => can(v.perm)).map((v) =>
      h("button", { class: `nav ${state.view === v.id ? "active" : ""}`, onclick: () => go(v.id) }, v.label));
    const side = h("aside", { class: "side" },
      h("div", { class: "brand" }, h("span", {}, "Project Bytes"), h("b", {}, "ROOT COCKPIT")),
      nav,
      h("div", { class: "who" },
        h("div", {}, h("b", {}, state.me.username), " ", pill(state.me.role, "info")),
        h("div", { class: "row small" },
          h("button", { class: "tiny ghost", onclick: changePassword }, "Password"),
          h("button", { class: "tiny ghost", onclick: () => signOut(true) }, "Sign out"))));
    app.append(side, h("main", { class: "main", id: "view" }));
    go(state.view);
  }

  function go(id) {
    const view = VIEWS.find((v) => v.id === id && can(v.perm)) || VIEWS[0];
    state.view = view.id;
    document.querySelectorAll(".nav").forEach((b) => b.classList.toggle("active", b.textContent === view.label));
    clearInterval(state.timer);
    const container = $("#view");
    const draw = async () => {
      if (document.hidden || $(".modal-backdrop")) return; // don't yank the page from under an open dialog
      const content = await view.render();
      if (content && state.view === view.id) container.replaceChildren(content);
    };
    draw();
    if (view.refresh) state.timer = setInterval(draw, view.refresh);
  }

  const refresh = () => go(state.view);

  async function changePassword() {
    const v = await ask({ title: "Change your password", noReason: true, fields: [
      { name: "current", label: "Current password", type: "password" },
      { name: "new", label: "New password (12+ characters)", type: "password" }] });
    if (v) await run(() => api("POST", "/admin/v1/me/password", { current: v.current, new: v.new }), "Password changed");
  }

  function header(title, ...extra) {
    return h("div", { class: "head" }, h("h2", {}, title), h("div", { class: "spacer" }), extra);
  }

  // ---- Commands (shared) ---------------------------------------------------------------------------

  async function sendCommand(type, target, preset = {}) {
    const fields = [];
    if (type === "broadcast" || type === "message") fields.push({ name: "message", label: "Message players will see", type: "textarea", value: preset.message });
    if (type === "broadcast") fields.push({ name: "style", label: "Style", type: "select", options: ["info", "warning", "event", "gift"], value: "info" });
    if (type === "kick") fields.push({ name: "message", label: "Message shown to the player (optional)", placeholder: "Removed by staff" });
    if (type === "shutdown") {
      fields.push({ name: "delaySeconds", label: "Countdown (seconds)", type: "number", value: 60, min: 0, max: 600 });
      fields.push({ name: "message", label: "Message", value: "This district is restarting for maintenance" });
    }
    if (type === "exec") fields.push({ name: "consoleCommand", label: "Server console command", placeholder: "e.g. stat net" });
    const labels = { broadcast: "Broadcast", message: "Message player", kick: "Kick player", shutdown: "Shut down server", refresh_character: "Refresh player data", exec: "Run console command" };
    const where = target.type === "all" ? "every server" : target.type === "district" ? `all ${target.id} instances` : target.label || target.id;
    const v = await ask({ title: `${labels[type]} - ${where}`, fields, danger: ["kick", "shutdown", "exec"].includes(type),
      message: type === "exec" ? "Runs directly on the dedicated server. Owner-level action." : "" });
    if (!v) return;
    const body = Object.assign({ type, target, reason: v.reason }, v);
    if (target.type === "character") body.characterId = target.id;
    if (body.delaySeconds !== undefined) body.delaySeconds = Number(body.delaySeconds);
    await run(() => api("POST", "/admin/v1/commands", body), (r) => `Queued for ${r.instances.join(", ")}`);
  }

  // ---- Overview ------------------------------------------------------------------------------------

  async function renderOverview() {
    const data = await run(() => api("GET", "/admin/v1/overview"));
    if (!data) return null;
    const s = data.stats;
    const tile = (k, v, sub) => h("div", { class: "tile" }, h("div", { class: "k" }, k), h("div", { class: "v" }, v), sub ? h("div", { class: "muted small" }, sub) : null);
    const districtRows = data.districts.map((d) => {
      const fill = d.capacity ? d.online / d.capacity : 0;
      const bar = h("div", { class: "bar" }, h("i"));
      bar.firstChild.style.width = `${Math.round(fill * 100)}%`;
      return h("tr", {}, h("td", {}, d.displayName), h("td", { class: "num" }, d.instances), h("td", { class: "num" }, `${num(d.online)} / ${num(d.capacity)}`), h("td", {}, bar));
    });
    const auditRows = data.recentAudit.map((a) => h("tr", {}, h("td", { class: "small muted" }, ago(a.at)), h("td", {}, a.staffName), h("td", { class: "mono" }, a.action), h("td", { class: "small" }, a.reason)));
    return h("div", { class: "stack" },
      header("Overview", can("server.command") ? h("button", { class: "primary", onclick: () => sendCommand("broadcast", { type: "all" }) }, "Broadcast to all") : null),
      h("div", { class: "grid tiles" },
        tile("Players online", num(s.online), `capacity ${num(s.capacity)}`),
        tile("District servers", num(s.servers), `${data.deployments.running} managed`),
        tile("Accounts", num(s.accounts), `${num(s.characters)} characters`),
        tile("Active bans", num(s.activeBans)),
        tile("Pending commands", num(s.pendingCommands)),
        tile("Active gifts", num(s.activeGifts))),
      h("div", { class: "grid two" },
        h("div", { class: "panel" }, h("h3", {}, "Districts"), table(["District", "#Instances", "#Online", "Load"], districtRows, "No district servers online.")),
        can("audit.read") ? h("div", { class: "panel" }, h("h3", {}, "Recent staff activity"), table(["When", "Staff", "Action", "Reason"], auditRows)) : null));
  }

  // ---- Deployment ----------------------------------------------------------------------------------

  async function renderDeploy() {
    const data = await run(() => api("GET", "/admin/v1/deployments"));
    if (!data) return null;
    const districts = state.catalog.districts;
    const district = h("select", {}, districts.map((d) => h("option", { value: d.districtId }, `${d.displayName} (${d.districtId})`)));
    const count = h("input", { type: "number", value: 1, min: 1, max: 16 });
    const region = h("input", { placeholder: "e.g. EU" });
    const maxPlayers = h("input", { type: "number", placeholder: "district default", min: 1 });
    const spawn = async () => {
      const v = await ask({ title: `Spin up ${count.value} x ${district.value}` });
      if (!v) return;
      await run(() => api("POST", "/admin/v1/deployments", { districtId: district.value, count: Number(count.value), region: region.value,
        maxPlayers: Number(maxPlayers.value || 0), reason: v.reason }), (r) => `Started ${r.started.length} instance(s)`);
      refresh();
    };
    const statusKind = { running: "good", starting: "info", stopping: "warn", stopped: "", exited: "bad" };
    const rows = data.deployments.map((d) => h("tr", {},
      h("td", { class: "mono small" }, d.deploymentId), h("td", {}, d.districtId), h("td", { class: "num" }, d.port),
      h("td", {}, pill(d.status, statusKind[d.status])), h("td", { class: "mono small" }, d.instanceId || "-"),
      h("td", { class: "small" }, `${d.startedBy}, ${ago(d.startedAt)}`),
      h("td", { class: "row" },
        h("button", { class: "tiny", onclick: () => showLog(d) }, "Log"),
        can("deploy") && ["starting", "running"].includes(d.status) ? h("button", { class: "tiny", onclick: () => stopDeployment(d, "graceful") }, "Stop") : null,
        can("deploy") && ["starting", "running", "stopping"].includes(d.status) ? h("button", { class: "tiny danger", onclick: () => stopDeployment(d, "force") }, "Kill") : null)));
    return h("div", { class: "stack" },
      header("Deployment"),
      data.configured ? null : h("div", { class: "banner" }, "Deployment isn't configured on this backend. Set deploy.serverExe (packaged server) or deploy.engineDir / UE_ENGINE_DIR (editor -server) in Backend/config.json."),
      can("deploy") ? h("div", { class: "panel" }, h("h3", {}, `Spin up instances (${data.mode}, max ${data.maxInstances})`),
        h("div", { class: "form" }, field("District", district), field("Count", count), field("Region tag", region), field("Max players", maxPlayers),
          h("button", { class: "primary", onclick: spawn, disabled: !data.configured }, "Spin up"))) : null,
      h("div", { class: "panel" }, h("h3", {}, "Managed instances"),
        table(["Deployment", "District", "#Port", "Status", "Instance", "Started", ""], rows, "Nothing started from the cockpit yet. Servers started by hand still appear under Servers & Sessions.")));
  }

  async function stopDeployment(d, mode) {
    const fields = mode === "graceful" ? [{ name: "delaySeconds", label: "Countdown for players (seconds)", type: "number", value: 60 },
      { name: "message", label: "Message", value: "This district is shutting down for maintenance" }] : [];
    const v = await ask({ title: `${mode === "force" ? "Kill" : "Stop"} ${d.instanceId || d.deploymentId}`, fields, danger: mode === "force",
      message: mode === "force" ? "Kills the process immediately. Players are disconnected without warning." : "Players get a countdown, then the server exits (killed if it hasn't after the grace period)." });
    if (!v) return;
    await run(() => api("POST", `/admin/v1/deployments/${d.deploymentId}/stop`, { mode, delaySeconds: Number(v.delaySeconds || 0), message: v.message, reason: v.reason }), "Stopping");
    refresh();
  }

  async function showLog(d) {
    const data = await run(() => api("GET", `/admin/v1/deployments/${d.deploymentId}/log`));
    if (data) ask({ title: `Log: ${d.districtId}:${d.port}`, wide: true, noReason: true, hideOk: true, body: h("pre", { class: "log" }, data.log || "(empty)") });
  }

  // ---- Servers & sessions --------------------------------------------------------------------------

  async function renderServers() {
    const [data, cmds] = await Promise.all([run(() => api("GET", "/admin/v1/servers")), run(() => api("GET", "/admin/v1/commands?limit=40"))]);
    if (!data) return null;
    const districtPick = h("select", {}, h("option", { value: "" }, "All servers"), state.catalog.districts.map((d) => h("option", { value: d.districtId }, d.displayName)));
    const targetFor = () => (districtPick.value ? { type: "district", id: districtPick.value } : { type: "all" });
    const cards = data.servers.map((s) => {
      const target = { type: "server", id: s.serverId, label: s.displayName };
      const players = s.players.map((p) => h("tr", {},
        h("td", {}, h("span", { class: `faction-${p.faction}` }, p.name), " ", h("span", { class: "muted small" }, `@${p.username}`)),
        h("td", { class: "num" }, p.rank), h("td", {}, p.threat),
        h("td", { class: "row" },
          can("server.command") ? h("button", { class: "tiny", onclick: () => sendCommand("message", { type: "character", id: p.characterId, label: p.name }) }, "Message") : null,
          can("player.kick") ? h("button", { class: "tiny danger", onclick: () => sendCommand("kick", { type: "character", id: p.characterId, label: p.name }) }, "Kick") : null,
          h("button", { class: "tiny ghost", onclick: () => openPlayer(p.accountId) }, "Profile"))));
      return h("div", { class: "panel" },
        h("div", { class: "row" }, h("b", {}, s.displayName), pill(`${s.population}/${s.maxPlayers}`, "info"), h("span", { class: "muted small mono" }, s.address), h("span", { class: "spacer" }),
          h("span", { class: "muted small" }, `heartbeat ${ago(s.lastSeen)}`)),
        h("div", { class: "row" },
          can("server.command") ? h("button", { class: "tiny", onclick: () => sendCommand("broadcast", target) }, "Broadcast") : null,
          can("server.command") ? h("button", { class: "tiny danger", onclick: () => sendCommand("shutdown", target) }, "Shutdown") : null,
          can("server.exec") ? h("button", { class: "tiny", onclick: () => sendCommand("exec", target) }, "Console") : null),
        table(["Player", "#Rank", "Threat", ""], players, "No players on this instance."));
    });
    const statusKind = { done: "good", failed: "bad", undeliverable: "bad", queued: "warn", delivered: "info" };
    const cmdRows = (cmds ? cmds.commands : []).map((c) => h("tr", {},
      h("td", { class: "small muted" }, ago(c.createdAt)), h("td", {}, c.createdBy), h("td", { class: "mono" }, c.type), h("td", { class: "mono small" }, c.instanceId),
      h("td", { class: "small" }, c.payload.message || c.payload.consoleCommand || c.payload.characterId || ""), h("td", {}, pill(c.status, statusKind[c.status])),
      h("td", { class: "small mono" }, c.result)));
    return h("div", { class: "stack" },
      header("Servers & Sessions"),
      can("server.command") ? h("div", { class: "panel" }, h("h3", {}, "Send to many"),
        h("div", { class: "row" }, districtPick,
          h("button", { onclick: () => sendCommand("broadcast", targetFor()) }, "Broadcast"),
          h("button", { class: "danger", onclick: () => sendCommand("shutdown", targetFor()) }, "Shutdown"),
          can("server.exec") ? h("button", { onclick: () => sendCommand("exec", targetFor()) }, "Console command") : null)) : null,
      cards.length ? h("div", { class: "grid two" }, cards) : h("div", { class: "panel empty" }, "No district servers online."),
      h("div", { class: "panel" }, h("h3", {}, "Recent commands"), table(["When", "By", "Type", "Instance", "Detail", "Status", "Result"], cmdRows)));
  }

  // ---- Players -------------------------------------------------------------------------------------

  let playerQuery = "";
  let openAccountId = "";

  function openPlayer(accountId) {
    openAccountId = accountId;
    go("players");
  }

  async function renderPlayers() {
    const search = h("input", { placeholder: "Username, character name or id", value: playerQuery });
    const results = h("div");
    const detail = h("div");
    const doSearch = async () => {
      playerQuery = search.value;
      const data = await run(() => api("GET", `/admin/v1/players?q=${encodeURIComponent(playerQuery)}`));
      if (!data) return;
      results.replaceChildren(table(["Account", "Characters", "Status", ""], data.players.map((p) => h("tr", {},
        h("td", {}, h("b", {}, p.username), h("div", { class: "muted small mono" }, p.accountId)),
        h("td", {}, p.characters.map((c) => h("div", {}, h("span", { class: `faction-${c.faction}` }, c.name), h("span", { class: "muted small" }, ` r${c.rank} ${c.threat}`), c.onlineInstance ? [" ", pill(c.onlineInstance, "good")] : null))),
        h("td", {}, p.banned ? pill("banned", "bad") : pill("ok", "good"), " ", p.flags.map((f) => pill(f))),
        h("td", {}, h("button", { class: "tiny", onclick: () => { openAccountId = p.accountId; loadDetail(); } }, "Open")))), "No players match."));
    };
    const loadDetail = async () => {
      if (!openAccountId) return;
      const view = await playerDetail(openAccountId);
      if (view) detail.replaceChildren(view);
    };
    search.addEventListener("keydown", (e) => { if (e.key === "Enter") doSearch(); });
    await doSearch();
    await loadDetail();
    return h("div", { class: "stack" },
      header("Players"),
      h("div", { class: "row" }, search, h("button", { class: "primary", onclick: doSearch }, "Search")),
      h("div", { class: "grid split" }, h("div", { class: "panel" }, h("h3", {}, "Results"), results), detail));
  }

  async function playerDetail(accountId) {
    const d = await run(() => api("GET", `/admin/v1/players/${accountId}`));
    if (!d) return null;
    const reload = () => { openAccountId = accountId; go("players"); };
    const a = d.account;
    const activeBan = d.bans.find((b) => b.active);

    const actions = h("div", { class: "row" },
      can("player.ban") && !activeBan ? h("button", { class: "danger", onclick: async () => {
        const v = await ask({ title: `Ban ${a.username}`, danger: true, fields: [
          { name: "durationHours", label: "Duration", type: "select", value: "24", options: [
            { value: "1", label: "1 hour" }, { value: "24", label: "24 hours" }, { value: "72", label: "3 days" },
            { value: "168", label: "7 days" }, { value: "720", label: "30 days" }, { value: "0", label: "Permanent" }] },
          { name: "publicReason", label: "Reason shown to the player", placeholder: "e.g. Cheating (aimbot)" }],
          message: "Ends their sessions and kicks any online character." });
        if (v) { await run(() => api("POST", `/admin/v1/players/${accountId}/ban`, { durationHours: Number(v.durationHours), publicReason: v.publicReason, reason: v.reason }), "Banned"); reload(); }
      } }, "Ban") : null,
      can("player.sessions") ? h("button", { onclick: async () => {
        const v = await ask({ title: `End ${a.username}'s sessions`, fields: [{ name: "kick", label: "Also kick from districts", type: "checkbox", value: true }] });
        if (v) { await run(() => api("POST", `/admin/v1/players/${accountId}/sessions/revoke`, { kick: v.kick, reason: v.reason }), "Sessions ended"); reload(); }
      } }, "Force logout") : null,
      can("player.flags") ? h("button", { onclick: async () => {
        const v = await ask({ title: `Account flag for ${a.username}`, fields: [{ name: "flag", label: "Flag", placeholder: "tester, premium..." },
          { name: "enabled", label: "Enabled", type: "select", options: [{ value: "1", label: "Add" }, { value: "0", label: "Remove" }], value: "1" }] });
        if (v) { await run(() => api("POST", `/admin/v1/players/${accountId}/flags`, { flag: v.flag, enabled: v.enabled === "1", reason: v.reason }), "Flags updated"); reload(); }
      } }, "Flags") : null,
      can("economy.grant") ? h("button", { class: "primary", onclick: () => grantDialog(d).then(reload) }, "Give") : null,
      can("economy.gift") ? h("button", { onclick: () => giftDialog({ target: "account", accountId, label: a.username }).then(reload) }, "Send mail gift") : null);

    const chars = d.characters.map((c) => h("div", { class: "panel" },
      h("div", { class: "row" }, h("b", { class: `faction-${c.faction}` }, c.name), h("span", { class: "muted small" }, `${c.faction} - rank ${c.rank} - ${c.threat} - $${num(c.money)}`),
        c.onlineInstance ? pill(c.onlineInstance, "good") : null, h("span", { class: "spacer" }),
        c.onlineInstance && can("server.command") ? h("button", { class: "tiny", onclick: () => sendCommand("message", { type: "character", id: c.characterId, label: c.name }) }, "Message") : null,
        c.onlineInstance && can("player.kick") ? h("button", { class: "tiny danger", onclick: () => sendCommand("kick", { type: "character", id: c.characterId, label: c.name }) }, "Kick") : null),
      table(["Item", "#Qty", "Expires", "Source", ""], c.inventory.map((i) => h("tr", {},
        h("td", {}, i.displayName, h("span", { class: "muted small" }, ` ${i.category}`)), h("td", { class: "num" }, i.quantity),
        h("td", { class: "small" }, i.expiresAt ? fmtTime(i.expiresAt) : "never"), h("td", { class: "small mono" }, i.source),
        h("td", {}, can("economy.grant") ? h("button", { class: "tiny danger", onclick: async () => {
          const v = await ask({ title: `Remove ${i.displayName} from ${c.name}`, danger: true });
          if (v) { await run(() => api("POST", "/admin/v1/grants", { characterId: c.characterId, removeEntryId: i.entryId, reason: v.reason }), "Removed"); reload(); }
        } }, "Remove") : null))), "Empty inventory.")));

    const banRows = d.bans.map((b) => h("tr", {}, h("td", {}, b.active ? pill("active", "bad") : pill(b.revokedAt ? "revoked" : "expired")),
      h("td", {}, b.reason), h("td", { class: "small" }, `${b.createdBy}, ${fmtTime(b.createdAt)}`), h("td", { class: "small" }, b.expiresAt ? fmtTime(b.expiresAt) : "permanent"),
      h("td", {}, b.active && can("player.ban") ? h("button", { class: "tiny", onclick: () => revokeBan(b).then(reload) }, "Revoke") : null)));

    return h("div", { class: "stack" },
      h("div", { class: "panel stack" },
        h("div", { class: "row" }, h("h2", {}, a.username), activeBan ? pill("BANNED", "bad") : null, a.flags.map((f) => pill(f)), h("span", { class: "spacer" }),
          h("span", { class: "muted small mono" }, a.accountId)),
        h("div", { class: "muted small" }, `Created ${fmtTime(a.createdAt)} - ${a.activeSessions} active session(s) - ${d.characters.length}/${a.maxCharacters} characters`),
        h("div", { class: "row" }, d.wallet.map((w) => pill(`${num(w.amount)} ${w.displayName}`, "info"))),
        actions),
      chars,
      h("div", { class: "panel" }, h("h3", {}, "Bans"), table(["", "Reason", "By", "Until", ""], banRows, "No bans.")),
      h("div", { class: "panel" }, h("h3", {}, "Unclaimed mail"), table(["Subject", "Contents", "Sent"], d.mailbox.map((m) => h("tr", {},
        h("td", {}, m.subject), h("td", { class: "small" }, m.attachments.map((x) => x.displayName).join(", ")), h("td", { class: "small" }, ago(m.createdAt)))), "Mailbox empty.")),
      d.audit.length ? h("div", { class: "panel" }, h("h3", {}, "Staff actions on this player"), auditTable(d.audit)) : null);
  }

  async function grantDialog(d) {
    const cat = state.catalog;
    const charOptions = d.characters.map((c) => ({ value: c.characterId, label: c.name }));
    const v = await ask({ title: `Give to ${d.account.username}`, message: "Applied immediately. Online characters are refreshed in their district.", fields: [
      { name: "kind", label: "What", type: "select", options: [{ value: "currency", label: "Currency" }, { value: "item", label: "Item" }], value: "currency" },
      { name: "characterId", label: "Character (for $ and items)", type: "select", options: [{ value: "", label: "(account)" }].concat(charOptions), value: charOptions[0] ? charOptions[0].value : "" },
      { name: "currency", label: "Currency", type: "select", options: cat.currencies.map((c) => ({ value: c.id, label: `${c.displayName} (${c.scope})` })) },
      { name: "amount", label: "Amount (negative removes)", type: "number", value: 1000 },
      { name: "itemId", label: "Item", type: "select", options: cat.items.map((i) => ({ value: i.id, label: `${i.displayName} [${i.category}]` })) },
      { name: "quantity", label: "Quantity", type: "number", value: 1, min: 1 },
      { name: "notifyMessage", label: "Tell the player (optional, if online)", placeholder: "A little something from the team" }] });
    if (!v) return;
    const body = { reason: v.reason, notifyMessage: v.notifyMessage };
    if (v.characterId) body.characterId = v.characterId; else body.accountId = d.account.accountId;
    if (v.kind === "currency") Object.assign(body, { currency: v.currency, amount: Number(v.amount) });
    else Object.assign(body, { itemId: v.itemId, quantity: Number(v.quantity) });
    await run(() => api("POST", "/admin/v1/grants", body), "Granted");
  }

  async function revokeBan(b) {
    const v = await ask({ title: `Revoke ban on ${b.username || b.accountId}` });
    if (v) await run(() => api("POST", `/admin/v1/bans/${b.banId}/revoke`, { reason: v.reason }), "Ban revoked");
  }

  // ---- Rewards & gifts -----------------------------------------------------------------------------

  function attachmentEditor() {
    const cat = state.catalog;
    const list = h("div", { class: "stack" });
    const addRow = (kind) => {
      const type = h("select", {}, h("option", { value: "currency", selected: kind === "currency" }, "Currency"), h("option", { value: "item", selected: kind === "item" }, "Item"));
      // Default to the account-wide currency (BP): it doesn't depend on which character claims the gift.
      const preferred = (cat.currencies.find((c) => c.scope === "account") || cat.currencies[0] || {}).id;
      const currency = h("select", {}, cat.currencies.map((c) => h("option", { value: c.id, selected: c.id === preferred }, c.displayName)));
      const item = h("select", {}, cat.items.map((i) => h("option", { value: i.id }, `${i.displayName} [${i.category}]`)));
      const amount = h("input", { type: "number", value: kind === "item" ? 1 : 500, min: 1 });
      const sync = () => { currency.hidden = type.value !== "currency"; item.hidden = type.value !== "item"; };
      type.addEventListener("change", sync);
      const row = h("div", { class: "row" }, type, currency, item, amount, h("button", { type: "button", class: "tiny ghost", onclick: () => row.remove() }, "Remove"));
      row.read = () => type.value === "currency" ? { type: "currency", currency: currency.value, amount: Number(amount.value) }
        : { type: "item", itemId: item.value, quantity: Number(amount.value) };
      sync();
      list.append(row);
    };
    addRow("currency");
    const el = h("div", { class: "stack" }, list, h("div", { class: "row" },
      h("button", { type: "button", class: "tiny", onclick: () => addRow("currency") }, "+ Currency"),
      h("button", { type: "button", class: "tiny", onclick: () => addRow("item") }, "+ Item")));
    el.read = () => [...list.children].map((r) => r.read());
    return el;
  }

  async function giftDialog(target) {
    const editor = attachmentEditor();
    const toAll = target.target === "all";
    const v = await ask({
      title: toAll ? "Gift every player" : `Mail a gift to ${target.label}`, danger: toAll, wide: true, okText: toAll ? "Send to everyone" : "Send",
      message: toAll ? "Every account gets this in their mailbox (claimed onto a character of their choice)." : "Delivered to their mailbox.",
      body: field("Attachments", editor),
      confirmPhrase: toAll ? state.catalog.giftAllConfirmation : null,
      fields: [
        { name: "subject", label: "Subject", placeholder: "Launch week reward" },
        { name: "body", label: "Message", type: "textarea" },
        { name: "expiresInDays", label: "Claimable for (days, 0 = forever)", type: "number", value: 30 },
        toAll ? { name: "includeNewAccounts", label: "Also for accounts created later", type: "checkbox", value: false } : null,
        toAll ? { name: "announce", label: "Announce in all districts", type: "checkbox", value: true } : null,
      ].filter(Boolean),
    });
    if (!v) return;
    await run(() => api("POST", "/admin/v1/gifts", {
      target: target.target, accountId: target.accountId, subject: v.subject, body: v.body, attachments: editor.read(),
      expiresInDays: Number(v.expiresInDays || 0), includeNewAccounts: !!v.includeNewAccounts, announce: !!v.announce,
      confirm: v.confirm, reason: v.reason }), (r) => `Sent to ${num(r.recipients)} account(s)`);
  }

  async function renderEconomy() {
    const data = await run(() => api("GET", "/admin/v1/gifts"));
    if (!data) return null;
    const giftRows = data.globalGifts.map((g) => h("tr", {},
      h("td", {}, g.subject), h("td", { class: "small" }, g.attachments.map((x) => x.displayName).join(", ")),
      h("td", { class: "num" }, num(g.claims)), h("td", { class: "small" }, `${fmtTime(g.createdAt)}${g.includeNewAccounts ? " (+ new accounts)" : ""}`),
      h("td", { class: "small" }, g.revokedAt ? pill("revoked") : g.expiresAt ? fmtTime(g.expiresAt) : "never"),
      h("td", {}, !g.revokedAt && can("economy.gift_all") ? h("button", { class: "tiny danger", onclick: async () => {
        const v = await ask({ title: `Revoke "${g.subject}"`, danger: true, message: "Players who haven't claimed it yet won't be able to. Already claimed rewards stay." });
        if (v) { await run(() => api("POST", `/admin/v1/gifts/${g.giftId}/revoke`, { reason: v.reason }), "Revoked"); refresh(); }
      } }, "Revoke") : null)));
    const mailRows = data.mail.map((m) => h("tr", {}, h("td", {}, m.username), h("td", {}, m.subject),
      h("td", { class: "small" }, m.attachments.map((x) => x.displayName).join(", ")), h("td", { class: "small" }, ago(m.createdAt)),
      h("td", {}, m.claimedAt ? pill("claimed", "good") : pill("unclaimed", "warn"))));
    return h("div", { class: "stack" },
      header("Rewards & Gifts",
        can("economy.gift_all") ? h("button", { class: "primary", onclick: () => giftDialog({ target: "all" }).then(refresh) }, "Gift all players") : null),
      h("p", { class: "muted" }, "To reward one player, open them under Players (Give for instant grants, Send mail gift for mailbox rewards)."),
      h("div", { class: "panel" }, h("h3", {}, "Gifts to everyone"), table(["Subject", "Contents", "#Claims", "Sent", "Expires", ""], giftRows, "No global gifts yet.")),
      h("div", { class: "panel" }, h("h3", {}, "Recent personal mail"), table(["Player", "Subject", "Contents", "Sent", ""], mailRows, "No mail sent yet.")));
  }

  // ---- Bans ----------------------------------------------------------------------------------------

  async function renderBans() {
    const onlyActive = h("input", { type: "checkbox" });
    const body = h("div");
    const load = async () => {
      const data = await run(() => api("GET", `/admin/v1/bans?active=${onlyActive.checked ? 1 : 0}`));
      if (!data) return;
      body.replaceChildren(table(["", "Player", "Reason", "Banned by", "Until", "Revoked", ""], data.bans.map((b) => h("tr", {},
        h("td", {}, b.active ? pill("active", "bad") : pill(b.revokedAt ? "revoked" : "expired")),
        h("td", {}, h("button", { class: "tiny ghost", onclick: () => openPlayer(b.accountId) }, b.username)),
        h("td", {}, b.reason), h("td", { class: "small" }, `${b.createdBy}, ${fmtTime(b.createdAt)}`),
        h("td", { class: "small" }, b.expiresAt ? fmtTime(b.expiresAt) : "permanent"),
        h("td", { class: "small" }, b.revokedAt ? `${b.revokedBy}: ${b.revokeReason}` : ""),
        h("td", {}, b.active && can("player.ban") ? h("button", { class: "tiny", onclick: () => revokeBan(b).then(load) }, "Revoke") : null))), "No bans."));
    };
    onlyActive.addEventListener("change", load);
    await load();
    return h("div", { class: "stack" }, header("Ban Log", h("label", { class: "check" }, onlyActive, "Active only")), h("div", { class: "panel" }, body));
  }

  // ---- Audit ---------------------------------------------------------------------------------------

  function auditTable(entries) {
    return table(["#", "When", "Staff", "Action", "Target", "Reason", "Details"], entries.map((a) => h("tr", {},
      h("td", { class: "num small muted" }, a.seq), h("td", { class: "small" }, fmtTime(a.at)), h("td", {}, a.staffName, h("div", { class: "muted small mono" }, a.ip)),
      h("td", { class: "mono" }, a.action), h("td", { class: "small mono" }, `${a.targetType} ${a.targetId}`), h("td", {}, a.reason),
      h("td", { class: "small mono" }, Object.keys(a.details || {}).length ? JSON.stringify(a.details) : ""))), "No entries.");
  }

  async function renderAudit() {
    const action = h("input", { placeholder: "action (e.g. ban, gift)" });
    const staffName = h("input", { placeholder: "staff" });
    const target = h("input", { placeholder: "target id" });
    const body = h("div");
    const chain = h("span");
    const load = async () => {
      const q = new URLSearchParams({ limit: "300", action: action.value, staff: staffName.value, target: target.value });
      const data = await run(() => api("GET", `/admin/v1/audit?${q}`));
      if (data) body.replaceChildren(auditTable(data.entries));
    };
    const verify = async () => {
      const r = await run(() => api("GET", "/admin/v1/audit/verify"));
      if (r) chain.replaceChildren(r.ok ? pill(`chain intact - ${r.entries} entries`, "good") : pill(`TAMPERED at entry #${r.brokenAt}`, "bad"));
    };
    [action, staffName, target].forEach((i) => i.addEventListener("keydown", (e) => { if (e.key === "Enter") load(); }));
    await load();
    await verify();
    return h("div", { class: "stack" },
      header("Audit Log", chain, h("button", { onclick: verify }, "Verify chain")),
      h("div", { class: "row" }, action, staffName, target, h("button", { class: "primary", onclick: load }, "Filter")),
      h("div", { class: "panel" }, body));
  }

  // ---- Staff ---------------------------------------------------------------------------------------

  async function renderStaff() {
    const data = await run(() => api("GET", "/admin/v1/staff"));
    if (!data) return null;
    const roles = Object.keys(state.catalog.roles);
    const create = async () => {
      const v = await ask({ title: "Add staff member", fields: [
        { name: "username", label: "Username" }, { name: "password", label: "Initial password (12+ chars)", type: "password" },
        { name: "role", label: "Role", type: "select", options: roles, value: "moderator" }] });
      if (!v) return;
      const r = await run(() => api("POST", "/admin/v1/staff", v), "Staff member created");
      if (r) { showSecret(`2FA for ${r.staff.username}`, r.totpSecret, r.totpUri); refresh(); }
    };
    const rows = data.staff.map((s) => h("tr", {},
      h("td", {}, h("b", {}, s.username), s.staffId === state.me.staffId ? h("span", { class: "muted small" }, " (you)") : null),
      h("td", {}, pill(s.role, "info")), h("td", {}, s.twoFactor ? pill("2FA", "good") : pill("no 2FA", "bad")),
      h("td", {}, s.disabled ? pill("disabled", "bad") : pill("active", "good")),
      h("td", { class: "small" }, s.lastLoginAt ? ago(s.lastLoginAt) : "never"), h("td", { class: "small" }, s.createdBy),
      h("td", { class: "row" },
        h("button", { class: "tiny", onclick: async () => {
          const v = await ask({ title: `Change role of ${s.username}`, fields: [{ name: "role", label: "Role", type: "select", options: roles, value: s.role }] });
          if (v) { await run(() => api("POST", `/admin/v1/staff/${s.staffId}`, { role: v.role, reason: v.reason }), "Role changed"); refresh(); }
        } }, "Role"),
        s.staffId !== state.me.staffId ? h("button", { class: `tiny ${s.disabled ? "" : "danger"}`, onclick: async () => {
          const v = await ask({ title: `${s.disabled ? "Enable" : "Disable"} ${s.username}`, danger: !s.disabled });
          if (v) { await run(() => api("POST", `/admin/v1/staff/${s.staffId}`, { disabled: !s.disabled, reason: v.reason }), "Updated"); refresh(); }
        } }, s.disabled ? "Enable" : "Disable") : null,
        h("button", { class: "tiny", onclick: async () => {
          const v = await ask({ title: `Reset 2FA for ${s.username}`, danger: true, message: "Their current authenticator stops working and they are signed out." });
          if (!v) return;
          const r = await run(() => api("POST", `/admin/v1/staff/${s.staffId}/reset-2fa`, { reason: v.reason }));
          if (r) showSecret(`New 2FA for ${s.username}`, r.totpSecret, r.totpUri);
        } }, "Reset 2FA"))));
    const roleRows = Object.entries(state.catalog.roles).map(([role, perms]) => h("tr", {}, h("td", {}, pill(role, "info")),
      h("td", { class: "small mono" }, perms.join(", ")), h("td", { class: "small mono" }, JSON.stringify(state.catalog.roleLimits[role] || {}))));
    return h("div", { class: "stack" },
      header("Staff", h("button", { class: "primary", onclick: create }, "Add staff")),
      h("div", { class: "panel" }, table(["Staff", "Role", "2FA", "Status", "Last sign-in", "Created by", ""], rows)),
      h("div", { class: "panel" }, h("h3", {}, "Roles"), table(["Role", "Permissions", "Limits"], roleRows)));
  }

  // ---- Start ---------------------------------------------------------------------------------------

  document.addEventListener("visibilitychange", () => { if (!document.hidden && state.me) refresh(); });
  if (state.token) boot(); else renderLogin();
})();
