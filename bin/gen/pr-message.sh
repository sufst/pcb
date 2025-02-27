#!/bin/sh

set -e

die() {
    2>&1 echo "$*"
    exit 1
}

if [ "$#" -ne 2 ]; then
    die "Usage: $0 <changes base ref> <user>"
fi

base="$1"
user="$2"

file=""

for changed_file in $(git diff "$base" --name-only); do
    if echo "$changed_file" | grep "kicad" >/dev/null; then
        file="$changed_file"
        break
    fi
done

if [ -z "$file" ]; then
    echo "Couldn't find KiCad project"
    exit 1
fi

dir="$(dirname "$file")"
release_dir="release/$dir"

pro="$(find "$dir/" -name "*.kicad_pro" -print | head -n 1)"
[ -z "$pro" ] && die "Couldn't find '*.kicad_pro' in '$dir/'"
pro_name="$(basename "$pro" ".kicad_pro")"
sch="$dir/$pro_name.kicad_sch"
[ -f "$sch" ] || die "Couldn't find '$sch'"
pcb="$dir/$pro_name.kicad_pcb"
[ -f "$pcb" ] || die "Couldn't find '$pcb'"

info_file="$release_dir/info"

already_exists=0
old_version=""
new_version="v1.0.0"

if [ -e "$release_dir" ]; then
    already_exists=1
    if [ -f "$info_file" ]; then
        old_version="$(grep "version: " "$info_file" | sed 's/.*version: \([A-z0-9\.]\+\).*/\1/' | head -n 1)"
        if [ -n "$old_version" ]; then
            new_version="$(echo "$old_version" | awk -F. -v OFS=. '{$NF=$NF+1;print}')"
        fi
    fi
fi

set +e # Carry on even if grep finds zero layers
n_layers="$(grep ".Cu\" signal" "$pcb" -c)"
set -e

echo "@$user Can automatically generate release files for this pull request."
echo ""
if [ "$already_exists" = "1" ]; then
    if [ -n "$old_version" ]; then
        echo "Found existing release files with version '$old_version'."
        echo ""
    fi
    echo "**Running this will overwrite the existing release files at \`$release_dir\`** "
    echo ""
fi 
echo "To continue, copy and paste (adjusting if necessary) the following into a new message:"
echo ""
echo "\`\`\`"
echo "@github-actions generate"
echo "project=$pro_name"
echo "new_version=$new_version"
echo "release_dir=$release_dir"
echo "sch_location=$sch"
echo "pcb_location=$pcb"
echo "n_layers=$n_layers"
echo "overwrite=$already_exists"
echo "create_tag=1"
echo "\`\`\`"
echo ""
echo "This will generate:"
echo "- \`$release_dir/info\`"
echo "- \`$release_dir/Schematic.pdf\`"
echo "- \`$release_dir/Fabrication.zip\`"
echo "- \`$release_dir/ibom.html\` ([link](https://github.com/openscopeproject/InteractiveHtmlBom))"
echo ""
echo "See [the README](https://github.com/sufst/pcb/?tab=readme-ov-file#releases) for more information."