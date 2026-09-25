#!/usr/bin/env sh
# Project Bytes playtest launcher. Examples:  ./playtest.sh up -d financial=2 -c 2   |   ./playtest.sh status
exec python3 "$(dirname "$0")/Tools/bytes.py" "$@"
