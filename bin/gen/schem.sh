#!/bin/sh

set -e

tmp_dir="$(date +"tmp-%Y.%m.%d-%H.%M.%S")"

cleanup() {
    rm -rf "$tmp_dir"
}

die() {
    echo "$*"
    cleanup
    exit 1
}

if [ $# -lt 2 ]; then
    die "Usage: $0 <sch> <release dir>"
fi

sch="$1"
[ -f "$sch" ] || die "PCB '$sch' doesn't exist"
release_dir="$2"
[ -d "$release_dir" ] || die "Release dir '$release_dir' doesn't exist or isn't a directory"

kicad-cli sch export pdf --no-background-color --output "$release_dir/Schematic.pdf" "$sch"
