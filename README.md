# HeloEnv

A [Gymnasium](https://gymnasium.farama.org/) environment wrapping a C-based
helicopter flight dynamics model, for training reinforcement learning agents
with PyTorch.

## Project Layout

```
HeloEnv/
├── .venv/                     # Local virtual environment (gitignored, not committed)
├── src/helo_env/
│   ├── __init__.py            # Registers "HeloEnv-v0" with gymnasium
│   ├── envs/
│   │   └── helo_env.py        # gymnasium.Env subclass, defines action/obs space
│   ├── native/                # C model lives/compiles here
│   │   ├── include/           # C headers
│   │   ├── src/                # C source files from your advisor
│   │   ├── build/             # Compiled shared library output (gitignored)
│   │   ├── CMakeLists.txt     # Build config for the C model -> .so/.dll/.dylib
│   │   └── bindings.py        # ctypes bridge exposing C functions to Python
│   └── utils/                 # Shared helpers (unit conversions, state vectors, etc.)
├── tests/                     # pytest unit tests
├── examples/                  # Example scripts (random agent, manual maneuver run)
├── scripts/                   # Build/setup helper scripts
├── .github/workflows/         # CI (lint + test)
├── .gitignore
├── LICENSE
├── pyproject.toml
└── README.md
```

## Setup

1. **Create and activate the virtual environment**:
   ```bash
   python3 -m venv .venv
   source .venv/bin/activate      # Windows: .venv\Scripts\activate
   ```

2. **Drop in the C model** into `src/helo_env/native/src/`
   (and any headers into `src/helo_env/native/include/`).

3. **Build the native shared library**:
   ```bash
   bash scripts/build_native.sh
   ```
   This runs CMake against `src/helo_env/native/` and outputs a shared library
   (`.so`/`.dylib`/`.dll`) into `src/helo_env/native/build/`, which is loaded
   at runtime via `ctypes` in `src/helo_env/native/bindings.py`.

4. **Install the package (editable, with dev dependencies)**:
   ```bash
   pip install -e ".[dev]"
   ```

5. **Verify the environment registers and steps correctly**:
   ```bash
   pytest tests/
   ```

## Usage

```python
import gymnasium as gym
import helo_env  # noqa: F401  (triggers gymnasium.register)

env = gym.make("HeloEnv-v0")
obs, info = env.reset()
action = env.action_space.sample()
obs, reward, terminated, truncated, info = env.step(action)
```

### Direct maneuver entry

```python
from helo_env.maneuvers.registry import get_maneuver

maneuver = get_maneuver("hover_to_forward_flight")
env = gym.make("HeloEnv-v0", maneuver=maneuver)
```

## Notes on the C Model Integration
C source files (`.c`) go in native src. They will be picked up
automatically by `native/CMakeLists.txt` via a glob and compiled into the
`helo_model` shared library.

C headers (`.h`) go in native include. This directory is added as a public
include path in `native/CMakeLists.txt`.

`bindings.py` uses `ctypes` rather than a compiled Python extension (e.g.
pybind11) so that the C source can be dropped in with minimal changes and
rebuilt independently of the Python package. If the model instead turns out
to expose a friendlier interface (e.g. already has Python bindings, or is
better suited to pybind11/nanobind), swap out `native/bindings.py` and
`native/CMakeLists.txt` accordingly — the rest of the package (`envs/`,
`controllers/`, `maneuvers/`) only depends on the Python-level interface
defined in `bindings.py`, not on the underlying binding technology.

## License

MIT — see [LICENSE](LICENSE).
