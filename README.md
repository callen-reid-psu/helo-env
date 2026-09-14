# HeloEnv

A [Gymnasium](https://gymnasium.farama.org/) environment wrapping a C-based helicopter flight dynamics model, for training reinforcement learning agents
with PyTorch.

## Version
1.0.0

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
Note: Setup instructions and scripts have only been verified on a system running WSL and Windows. 

1. **Create and activate the virtual environment**:

   Open a terminal in VSCode and run the following:
   
   **Bash**:
   ```bash
   python3 -m venv .venv
   source .venv/bin/activate
   ```
   **Powershell**:
   ```powershell
   python3 -m venv .venv
   .\.venv\Scripts\activate
   ```

2. **Install the package (editable, with dev dependencies)**:
   ```bash
   pip install -e ".[dev]"
   ```

3. **Verify the environment registers and steps correctly**:
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

## Development
**Updating the C model**
1. **Replacing the Source Files**:
   1. Create a new branch for the updated model. 
   2. Remove all `.c` files from `src/helo_env/native/src`. 
   3. **Excluding** `tmwtypes.h` remove all header files from `src/helo_env/native/include`. 
   4. Proceed with the following commands based on your opperating system.

   **Bash**
   ```bash
   bash scripts/import_model.sh ~/{MODEL_PATH}                       # Linux Paths
   bash scripts/import_coder_output.sh "$(wslpath '{WINDOWS_PATH}')" # Windows Paths
   ```
   **Powershell**
   ```powershell
   .\scripts\Import-Model.ps1
   ```
2. **Verify Required Packages are installed**:
   Verify Cmake:
   ```bash
   cmake --version
   
   ```

   If it is not installed download from https://cmake.org/download/ and check "Add CMake to system PATH" during install.

   Verify gcc and mingw32-make:
   ```bash
   gcc --version
   mingw32-make --version
   ```

   If they are not installed download from https://www.msys2.org/ and follow instructions on the page.
   
3. **Build the native library**:
   If an existing `cmaker-build` folder is present in the `native` directory delete the folder then run.
   **Linux**:
   ```bash
   bash scripts/build_native.sh
   ```
   **Windows**:
   ```powershell
   .\scripts\Build-Native.ps1 -Generator "MinGW Makefiles"
   ```
   This runs CMake against `src/helo_env/native/` and outputs a shared library
   (`.so`/`.dylib`/`.dll`) into `src/helo_env/native/build/`, which is loaded
   at runtime via `ctypes` in `src/helo_env/native/bindings.py`.

## License

Academic Use — see [LICENSE](LICENSE).
