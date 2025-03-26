#!/bin/bash

#
## Finds all root schematics in the provided directory
#

set -e

die() {
    echo "$*"
    exit 1
}

# Returns the UUID of the provided file (file should be a .kicad_sch)
get_sch_id() {
    grep uuid "$1" | head -n 1 | sed 's/^.*(uuid[^"]*"//;s/").*$//'
}

path="$1"

if ! [ -e "$path" ]; then
    die "'$path' does not exist"
fi

dir="$(dirname "$path")"
if [ -n "$path" ]; then
    cd "$dir"
fi

for project in *.kicad_pro; do
    if ! [ -f "$project" ]; then
        break # no projects in this directory
    fi
    root_sch_id="$(grep -B 1 Root "$project" | head -n 1 | sed 's/^[^"]*"//;s/",.*$//')"
    for schematic in *.kicad_sch; do
        if ! [ -f "$schematic" ]; then
            break # no schematics in this directory
        fi
        if [ "$(get_sch_id "$schematic")" = "$root_sch_id" ]; then
            if [ -n "$dir" ]; then
                echo "$dir/$schematic"
            else
                echo "$schematic"
            fi
        fi
    done
done
