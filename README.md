# OuluBSD/Eon

Visual dataflow graph studio, declarative scripting language DSL compiler, and high-performance Entity Component System (ECS) runtime for U++.

---

## Architecture & Package Structure

`OuluBSD/Eon` decouples visual node canvas workflows, declarative `.eon` machine scripting, and the ECS packet streaming engine into modular assemblies:

| Package | Path | Description |
|---|---|---|
| **`Eon`** | `uppsrc/Eon` | Core engine, script loaders (`machine`, `ecs`, `loop`, `driver`), and subsystem registration |
| **`Eon/Compiler`** | `uppsrc/Eon/Compiler` | Lexical, token, AST and semantic compiler for `.eon` domain-specific language |
| **`Ecs`** | `uppsrc/Ecs` | Real-time Entity Component System with typed channels, link systems, and packet routing |
| **`Vfs/Ecs`** | `uppsrc/Vfs/Ecs` | Backward-compatibility forwarding headers redirecting legacy `<Vfs/Ecs/*.h>` to `<Ecs/*.h>` |
| **`Node`** | `uppsrc/Node` | Core graph data structures, topological sorting, routing, and interactive canvas viewport |
| **`NodeWorkbench`** | `uppsrc/NodeWorkbench` | Multi-document visual IDE workbench with property grids, docking panes, and component pallets |

---

## Examples

### 1. `examples/NodeWorkbenchApp`
Full visual node workbench application with graph editing, panning, zooming, connecting pins, and `.eon` graph serialization.
- **Interactive Run**: `./bin/NodeWorkbenchApp`
- **Automated Verification**: `./bin/NodeWorkbenchApp --test` (loads `share/eon/tests/00a_audio_gen.eon`, validates node/edge connectivity, and exits 0).

### 2. `examples/EonDemo`
Headless demonstration of the `PacketRouter` topology and real-time streaming engine.
- **Interactive / Test Run**: `./bin/EonDemo --test` (configures source/sink ports, connects channels, routes 10 packets, validates delivery counters, and exits 0).

---

## Building with UppBuilder

Prerequisites:
- [OuluBSD/UppBuilder](https://github.com/OuluBSD/UppBuilder)
- [OuluBSD/BazaarCore](https://github.com/OuluBSD/BazaarCore)
- [OuluBSD/VFS](https://github.com/OuluBSD/VFS)
- [upstream ultimatepp](https://github.com/ultimatepp/ultimatepp)

### Build Commands

```bash
# Build headless packet router demo
uppbuilder examples/EonDemo -m CLANG --bazaarcore ../BazaarCore --vfs ../VFS

# Run headless test
./bin/EonDemo --test

# Build visual node studio
uppbuilder examples/NodeWorkbenchApp -m CLANG --bazaarcore ../BazaarCore --vfs ../VFS

# Run automated graph loader test
./bin/NodeWorkbenchApp --test
```

---

## Continuous Integration

Multiplatform CI runs automatically via GitHub Actions on:
- **Ubuntu Linux** (`gcc` and `clang`) with `xvfb-run`
- **macOS** (`clang`)
- **Windows** (`MSVC` via `MSVS22x64`)
