#!/bin/sh

# run kicad-cli once to generate .config/kicad/<version> then copy default lib tables
kicad-cli -v

for version in ~/.config/kicad/*; do 
    cp /usr/share/kicad/template/*-lib-table "$version/"
done
