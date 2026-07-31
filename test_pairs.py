#!/usr/bin/env python3
"""
Validate keygen_8FC8 against 12 known (service-tag -> master-password) pairs
harvested from Latitude 5530 systems, then emit a prediction for the target tag.
"""

from keygen import keygen_8FC8

PAIRS = [
    ("BC91NL3", "2XykI691322s03r4"),
    ("H9ZLSL3", "JR0WnRPERzRQzNq["),
    ("8VRTSL3", "msffe422daw5jde4"),
    ("9I87UL3", "mdgrr42PKq4hdr58"),
    ("FVTLLS3", "4Zh8hMBcksLEBM19"),
    ("8709FK3", "qnprBM2PP3rzLck2"),
    ("1NXQU23", "1BGLGGUJUjxZj12G"),
    ("5SR8TL3", "aUr[hhIRskszkpsM"),
    ("31WYGS3", "JQMLk265rz3QIkQI"),
    ("4GMSTL3", "sLkNM[BQ4L4Ixm34"),
    ("RE4FSE3", "Lsp01Mq8zZ42GzI["),
    ("GHJTR23", "xzdkGyjz6E9k3522"),
]

TARGET = "5XCQ5Y2"


def main() -> int:
    print(f"Validating {len(PAIRS)} pairs...\n")
    total = 0
    hits_primary = 0
    hits_secondary = 0
    for tag, expected in PAIRS:
        primary, secondary = keygen_8FC8(tag)
        p_ok = primary == expected
        s_ok = secondary == expected
        marker = "P" if p_ok else ("S" if s_ok else "-")
        print(f"  [{marker}]  {tag}  expect={expected}")
        print(f"            primary  ={primary}")
        print(f"            secondary={secondary}")
        total += 1
        hits_primary   += int(p_ok)
        hits_secondary += int(s_ok)
    print()
    print(f"Matches: primary={hits_primary}/{total}  secondary={hits_secondary}/{total}")
    print()
    print(f"Prediction for {TARGET}:")
    for pw in keygen_8FC8(TARGET):
        print(f"  {TARGET}-8FC8  {pw}")
    return 0 if (hits_primary == total or hits_secondary == total) else 1


if __name__ == "__main__":
    raise SystemExit(main())
