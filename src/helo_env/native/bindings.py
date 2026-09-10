"""ctypes bridge to the compiled C helicopter model.

Loads the shared library built via CMake (see native/CMakeLists.txt and
scripts/build_native.sh) and exposes a thin Python wrapper class, `HeloModel`,
around the model's C API.

Update `_FUNC_SIGNATURES` and `HeloModel` once the actual C API (function
names, argument types, struct layouts) from the advisor's code is known.
"""
from __future__ import annotations

import ctypes
import platform
from pathlib import Path

import numpy as np

_BUILD_DIR = Path(__file__).parent / "build"


def _library_filename() -> str:
    system = platform.system()
    if system == "Windows":
        return "libH60Sim.lib"
    return "libhelo_model.so"


def _load_library() -> ctypes.CDLL:
    lib_path = _BUILD_DIR / _library_filename()
    if not lib_path.exists():
        raise FileNotFoundError(
            f"Native helicopter model library not found at {lib_path}. "
            "Run `bash scripts/build_native.sh` after placing the C source "
            "in src/helo_env/native/src/."
        )
    return ctypes.CDLL(str(lib_path))


class HeloModel:
    """Thin Python wrapper around the C helicopter model's shared library.

    Placeholder implementation — wire up real function signatures once the
    C API is known, e.g.:

        self._lib.helo_create.restype = ctypes.c_void_p
        self._lib.helo_step.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_float), ...]
    """

    def __init__(self) -> None:
        self._lib = _load_library()
        self._handle = None  # opaque pointer returned by the C model, if any

    def reset(self) -> np.ndarray:
        # TODO: call into C reset function, return initial state vector.
        raise NotImplementedError("Wire up HeloModel.reset() to the C API.")

    def step(self, action: np.ndarray) -> tuple[np.ndarray, float, bool]:
        # TODO: call into C step function with `action`, return
        # (next_state, reward, terminated).
        raise NotImplementedError("Wire up HeloModel.step() to the C API.")

    def close(self) -> None:
        # TODO: call into C teardown/free function if the model allocates
        # persistent state.
        pass
