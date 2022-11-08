# PCBs

Central repository of all PCB design files.

## How To Use This Repo

### Git Limitations
It is not possible to resolve merge conflicts within individual design files, which is an unfortunate limitation of using `git` with KiCad. While KiCad files are in a text format, they aren't really designed to be edited manually. It is therefore *essential* that only one person is editing a particular file in a project at a time. Once someone starts working on a file, until it is merged into the `main` branch nobody else can edit that file. A good way to get round this is to use the "hierarchical sheets" feature to divide schematics into multiple files (if it can be done in a logical way).

### Files

Files that should be in this repo, under version control:
- Project files (`.kicad_pro`).
- Schematic files (`.kicad_sch`).
- PCB files (`.kicad_pcb`).
- Custom footprints (`.kicad_mod`).
- Custom symbols (`.kicad_sym`).
- Footprint library tables (`fp-lib-table`).
- Symbol library tables (`sym-lib-table`).
- 3D models of components (`.step` files).
- Simulation code (e.g. `.asc` files from LTSpice).

Files that should never be in here:
- Exports such as BOMs, gerbers, netlists, renders, etc.
- Local project settings (`.kicad_prl`).
- Project backups (.zip files generated in `<project name>-backups`, `.bak` `.bck` `-bak` files).
- Cache files (`fp-info-cache`).

The `.gitignore` should prevent the addition of files we don't want to keep in here, but before you commit make sure to do a quick check of what is actually being added.

