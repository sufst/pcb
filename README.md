# PCBs

## About
Central repository of all PCB design files. Includes:

| Folder    | Project Name                     |
|-----------|----------------------------------|
| bspd      | Brake System Plausibility Device |
| hv-sense  | High Voltage Sense               |
| latching  | Latch Circuit                    |
| precharge | Precharge Circuit                |
| segment   | Segment to BMS Connector         |
| tsal      | Tractive System Active Light     |
| vcu       | Vehicle Control Unit             |

## Version Control for KiCad Projects

### Why?
- Revert individual changes.
- Document development history via commits and GitHub issues.
- Easily view previous versions of designs.
- Manage shared library of components.

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

### Shared Resources

The `common` folder is used for resources which can be shared across multiple projects. This includes:

- Images (`images` subdirectory).
- 3D models (`step` subdirectory).
- Custom symbols (`sufst-lib.kicad_sym`).
- Custom footprints (`sufst-lib.pretty`).
- SUFST standard sheet layout (`sheet-layout.kicad_wks`).

> Note: Since projects were previously in their own individual repos, many designs still have their own libraries, step files, etc. These will gradually be migrated to the SUFST library.

### Library Paths
When you configure the library paths for a project (`sym-lib-table` and `fp-lib-table` data), make sure to always use a path relative to the project with the `${KIPRJMOD}` substitution.

- Correct: `${KIPRJMOD}/../common/sufst-lib.kicad_sym`
- Incorrect: `/Users/<your name>/Documents/sufst/pcb/common/sufst-lib.kicad_sym`

If an absolute path is used, when someone else opens the project that path will not exist and the library paths will not be valid. `-lib-table` files should never contain an absolute path.

### Git Limitations
It is not possible to resolve merge conflicts within individual design files, which is an unfortunate limitation of using `git` with KiCad. While KiCad files are in a text format, they aren't really designed to be edited manually. It is therefore *essential* that only one person is editing a particular file in a project at a time (including the shared library). Once someone starts working on a file, until it is merged into the `main` branch nobody else can edit that file. A good way to get round this is to use the "hierarchical sheets" feature to divide schematics into multiple files (if it can be done in a logical way).

