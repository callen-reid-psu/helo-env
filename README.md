# HeloEnv

A [Gymnasium](https://gymnasium.farama.org/) environment wrapping a C-based
helicopter flight dynamics model, for training reinforcement learning agents
with PyTorch.

## Project Layout

```
HeloEnv/
├── .venv/                     # Local virtual environment
├── src/helo_env/
│   ├── __init__.py            # Registers "HeloEnv-v0" with gymnasium
│   ├── envs/
│   │   └── helo_env.py        # gymnasium.Env subclass, defines action/obs space
│   ├── native/                # C model
│   │   ├── include/           # C headers
│   │   ├── src/               # C source files
│   │   ├── build/             # Compiled shared library output
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

   Open a bash terminal in VSCode and run the following:

   ```bash
   python3 -m venv .venv
   source .venv/bin/activate      # Windows: .venv\Scripts\activate
   ```

   If you do not have bash intalled see Git Bash Setup below.

2. **Import the C model**:
   ```bash
   bash scripts/import_model.sh ~/{MODEL_PATH}
   ```
   For Windows paths:
   ```bash
   bash scripts/import_coder_output.sh "$(wslpath '{WINDOWS_PATH}')"
   ```
   This imports all C files in the parent directory into `src/helo_env/native/src` and all header files in the parent directory into `src/helo_env/native/src`.

3. **Verify CMake is installed**:
   ```bash
   cmake --version
   ```
   If it is not installed download from https://cmake.org/download/ and check "Add CMake to system PATH" during install.
4. **Build the native shared library**:
   ```bash
   bash scripts/build_native.sh
   ```
   This runs CMake against `src/helo_env/native/` and outputs a shared library
   (`.so`/`.dylib`/`.dll`) into `src/helo_env/native/build/`, which is loaded
   at runtime via `ctypes` in `src/helo_env/native/bindings.py`.

5. **Install the package (editable, with dev dependencies)**:
   ```bash
   pip install -e ".[dev]"
   ```

6. **Verify the environment registers and steps correctly**:
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

## License

MIT — see [LICENSE](LICENSE).
