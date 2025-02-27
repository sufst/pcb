#!/bin/sh

set -e

start_dir="$(pwd)"
tmp_dir="$(date +"tmp-%Y.%m.%d-%H.%M.%S")"

cleanup() {
    cd "$start_dir"
    rm -rf "$tmp_dir"
}

die() {
    echo "$*"
    cleanup
    exit 1
}

if [ $# -lt 2 ]; then
    die "Usage: $0 <pcb> <release dir>"
fi

pcb="$1"
[ -f "$pcb" ] || die "PCB '$pcb' doesn't exist"
release_dir="$2"
[ -d "$release_dir" ] || die "Release dir '$release_dir' doesn't exist or isn't a directory"

mkdir -p "$tmp_dir"
cd "$tmp_dir"

# generate gerbers
kicad-cli pcb export gerbers "../$pcb" || die
zip -r Fabrication.zip ./* || die
mv Fabrication.zip "../$release_dir"

cleanup
