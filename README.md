# PCBs

## About
Central repository of all schematics and PCB design files.

| Folder     | Project                          | Project Code |
|------------|----------------------------------|--------------|
| ail        | Accumulator Indicator Light Logic| `ail`        |
| ail-led    | Accumulator Indicator Light Led  | `ail-led`    |
| batak      | Batak Game (non-car)             | `batak`      |
| break-light| Rear Break Light                 | `break-light`|
| bspd       | Brake System Plausibility Device | `bspd`       |
| can-node   | Voltage Reader and Broadcaster   | `can-node`   |
| curr-amp   | Current Sensor Amplifier         | `curr-amp`   |
| dash       | Dashboard                        | `dash`       |
| discharge  | Discharge Relay Breakout         | `discharge`  |
| hv-sense   | High Voltage Sense               | `hvs`        |
| latching   | Latch Circuit                    | `latching`   |
| loom*      | Loom Design                      | `loom`       |
| lvbms      | Low Voltage Battery Management System | `lvbms` |
| precharge  | Precharge Controller             | `precharge`  |
| segment    | Segment                          | `segment`    |
| telemetry  | On-Car Telemetry                 | `telemetry`  |
| test-rig   | PCB Test / Demo Rig              | `test`       |
| top-level* | Full Car Schematic               |              |
| trc        | TSAC Relay Controller            | `trc`        |
| tsal       | Tractive System Active Light     | `tsal`       |
| vcu        | Vehicle Control Unit             | `vcu`        |

We design our PCBs in KiCad (version 8+).

>*Moved to https://github.com/sufst/loom

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

## Releases

### Release Files
When a PCB is fabricated, a new 'release' for the given project should be 
created and stored within this repo in the `releases/<PROJECT NAME>` folder. 
This folder should contain the latest version (and ONLY the latest version) of
the following files:

1. Exported gerbers and drill files in a ZIP archive called `fabrication.zip`.
2. Schematic sheets as a PDF (`Schematic.pdf`).
3. Layout as a PDF in colour, with border and title block (`Layout.pdf`).
4. HTML iBOM created using the ["Interactive HTML BOM Plugin"](https://github.com/openscopeproject/InteractiveHtmlBom) (`ibom.html`).

Additionally, a file called `info` (no extension) should be created (if it 
doesn't already exist) containing release information in the following format:

```txt
version: <VERSION NUMBER>
date: <RELEASE DATE>
fabrication: <COMPANY>
```

Version numbers should be in the format `v1.0.1` and dates should be in the
format `YYYY-MM-DD`. For example:

```txt
version: v1.0.1
date: 2023-01-23
fabrication: JLCPCB
```

The release folder for a project should then have the following structure and 
file names:

```txt
<PROJECT NAME>
├── Layout.pdf
├── Schematic.pdf
├── fabrication.zip
├── ibom.html
└── info
```

When creating a new release, make sure to overwrite/replace all the existing 
files.

### Release Tag

The release commit should then be tagged with the following command:

```sh
git tag <PROJECT CODE>-<VERSION_NUMBER>
```

Tagging should be done **after** merging to `main`! Example command:

```sh
git tag segment-v1.0.1
```

To push tags to GitHub:

```sh
git push --tags
```
