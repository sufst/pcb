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

if [ $# -lt 3 ]; then
    die "Usage: $0 <sch> <pcb> <release dir> [--erc] [--drc]"
fi

sch="$1"
shift
test -f "$sch" || die "Schematic '$sch doesn't exist"
pcb="$1"
shift
test -f "$pcb" || die "PCB '$pcb' doesn't exist"
release_dir="$1"
shift
test -e "$release_dir" || die "Release dir '$release_dir' doesn't exist"

while test $# -gt 0
do
    case "$1" in
        --erc) RUN_ERC=1
            ;;
        --drc) RUN_DRC=1
            ;;
        *) die "Unreconised option $1"
            ;;
    esac
    shift
done

mkdir -p "$tmp_dir"
cd "$tmp_dir"

# generate gerbers
echo "../$pcb"
kicad-cli pcb export gerbers "../$pcb"
zip -r fabrication.zip ./*
mv fabrication.zip "../$release_dir"
#
cd ..
cleanup
#
INTERACTIVE_HTML_BOM_NO_DISPLAY=1 generate_interactive_bom "$pcb" --dest-dir "../$release_dir" --no-browser
kicad-cli sch export pdf --output "$release_dir/schematic.pdf" "$sch"

# gen erc-errors and drc-errors

set +e # Don't abort if ERC/DRC fails
[ "$RUN_ERC" = "1" ] && LOG_LOCATION="$release_dir/$(date +"erc-log-%Y.%m.%d-%H.%M.%S.txt")" ./bin/test/erc.sh "$sch"
[ "$RUN_DRC" = "1" ] && LOG_LOCATION="$release_dir/$(date +"drc-log-%Y.%m.%d-%H.%M.%S.txt")" ./bin/test/drc.sh "$pcb"
set -e
