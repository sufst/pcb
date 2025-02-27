#!/bin/sh

set -e

start_dir="$(pwd)"

die() {
    echo "$*"
    exit 1
}

if [ $# -lt 2 ]; then
    die "Usage: $0 <pcb> <release dir>"
fi

pcb="$1"
[ -f "$pcb" ] || die "PCB '$pcb' doesn't exist"
release_dir="$2"
[ -d "$release_dir" ] || die "Release dir '$release_dir' doesn't exist or isn't a directory"

INTERACTIVE_HTML_BOM_NO_DISPLAY=1 generate_interactive_bom "$pcb" --dest-dir "$start_dir/$release_dir" --no-browser
