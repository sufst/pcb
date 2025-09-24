#!/bin/sh

set -e

log="$(date +"rel-log-%Y.%m.%d-%H.%M.%S.json")"

cleanup() {
    rm -f "$log"
}

die() {
    if [ -n "$*" ]; then
        echo "$*"
    fi
    cleanup
    exit 1
}

path="$1"

if ! [ -f "$path" ]; then
    die "'$path' does not exist"
fi

if ! echo "$path" | grep "\-lib-table$" >/dev/null; then
    die "expected filename ending in '-lib-table'"
fi

if grep "^ *(lib.*(uri \"[^\$]" "$path" > "$log"; then
    echo "'$path' appears to not use a relative path:"
    cat "$log"
    die
fi

cleanup