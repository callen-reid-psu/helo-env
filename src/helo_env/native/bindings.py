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
# Fixed from the model (NOTE: Must change if change to controls impacts the NCTRLS)
NSTATES = 39
NCTRLS = 4
NOUT = 7


def _library_filename() -> str:
    system = platform.system()
    if system == "Windows":
        return "H60Sim.dll"
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


class FlightConditions(ctypes.Structure):
    """
    Flight Conditions Data Structure in the north, east, down frame.
    """
    _fields_ = [("vx_trim",ctypes.c_double),
                ("vy_trim",ctypes.c_double),
                ("vz_trim",ctypes.c_double),
                ("psid_trim",ctypes.c_double),
                ("psi_trim",ctypes.c_double), 
                ("z_trim",ctypes.c_double), 
                ("x_trim",ctypes.c_double), 
                ("y_trim",ctypes.c_double), 
                ]


class Constants(ctypes.Structure):
    """
    Constants Data Structure 
    """
    _fields_ = [
        ("d2r", ctypes.c_double),
        ("r2d", ctypes.c_double),
        ("D2R", ctypes.c_double),
        ("R2D", ctypes.c_double),
        ("g", ctypes.c_double),
        ("FtLb_s2Hp", ctypes.c_double),
        ("fps2kts", ctypes.c_double),
        ("kts2fps", ctypes.c_double),
        ("rhoSLSTD", ctypes.c_double),
        ("R", ctypes.c_double),
        ("NB", ctypes.c_double),
        ("OMEGA", ctypes.c_double),
        ("OMEGAT", ctypes.c_double),
        ("HOFFSET", ctypes.c_double),
        ("SPAR", ctypes.c_double),
        ("RSEG", ctypes.c_double * 10),
        ("DELSEG", ctypes.c_double * 10),
        ("DynTwistMode", ctypes.c_double * 10),
        ("TauDT", ctypes.c_double),
        ("TWISTTABR", ctypes.c_double * 21),
        ("TWISTTABTHET", ctypes.c_double * 21),
        ("BTL", ctypes.c_double),
        ("MBETA", ctypes.c_double),
        ("IBETA", ctypes.c_double),
        ("WBLADE", ctypes.c_double),
        ("G", ctypes.c_double),
        ("ALD", ctypes.c_double),
        ("BLD", ctypes.c_double),
        ("CLD", ctypes.c_double),
        ("DLD", ctypes.c_double),
        ("RLD", ctypes.c_double),
        ("THETALDGEO", ctypes.c_double),
        ("ITHSH", ctypes.c_double),
        ("IPHSH", ctypes.c_double),
        ("Tshaft", ctypes.c_double * 9),
        ("DELSP", ctypes.c_double),
        ("DELTA3", ctypes.c_double),
        ("CLAG", ctypes.c_double),
        ("KLAG", ctypes.c_double),
        ("ZETA0", ctypes.c_double),
        ("CFLAP", ctypes.c_double),
        ("KFLAP", ctypes.c_double),
        ("CHORDT", ctypes.c_double),
        ("CHORDR", ctypes.c_double),
        ("CHORD", ctypes.c_double * 10),
        ("istart", ctypes.c_double),
        ("inflow", ctypes.c_double),
        ("CLR0UTAB", ctypes.c_double * 181),
        ("AOAUTAB", ctypes.c_double * 181),
        ("CLR0BTAB", ctypes.c_double * 363),
        ("AOABTAB", ctypes.c_double * 33),
        ("MACHTAB", ctypes.c_double * 11),
        ("CDR0UTAB", ctypes.c_double * 181),
        ("CDR0BTAB", ctypes.c_double * 363),
        ("ACL1", ctypes.c_double),
        ("ACL2", ctypes.c_double),
        ("ACL3", ctypes.c_double),
        ("ACL4", ctypes.c_double),
        ("DCDMR", ctypes.c_double),
        ("KR", ctypes.c_double),
        ("KRsched", ctypes.c_double * 4),
        ("KRVsched", ctypes.c_double * 4),
        ("FSCG", ctypes.c_double),
        ("WLCG", ctypes.c_double),
        ("BLCG", ctypes.c_double),
        ("FSMR", ctypes.c_double),
        ("WLMR", ctypes.c_double),
        ("BLMR", ctypes.c_double),
        ("WEIGHT", ctypes.c_double),
        ("WEIGHTNR", ctypes.c_double),
        ("MASS", ctypes.c_double),
        ("IX", ctypes.c_double),
        ("IY", ctypes.c_double),
        ("IZ", ctypes.c_double),
        ("IXZ", ctypes.c_double),
        ("FSCGB", ctypes.c_double),
        ("WLCGB", ctypes.c_double),
        ("BLCGB", ctypes.c_double),
        ("IGNDEFF", ctypes.c_double),
        ("KGE1", ctypes.c_double),
        ("KGE2", ctypes.c_double),
        ("FUSEAOA", ctypes.c_double * 25),
        ("FUSEBETA", ctypes.c_double * 25),
        ("FUSEABETA", ctypes.c_double * 13),
        ("FUSEDA", ctypes.c_double * 25),
        ("FUSEDB", ctypes.c_double * 13),
        ("FUSEYB", ctypes.c_double * 25),
        ("FUSELA", ctypes.c_double * 25),
        ("FUSELB", ctypes.c_double * 25),
        ("FUSERB", ctypes.c_double * 25),
        ("FUSEMA", ctypes.c_double * 25),
        ("FUSEMB", ctypes.c_double * 13),
        ("FUSENB", ctypes.c_double * 25),
        ("FSfus", ctypes.c_double),
        ("BLfus", ctypes.c_double),
        ("WLfus", ctypes.c_double),
        ("FSTR", ctypes.c_double),
        ("BLTR", ctypes.c_double),
        ("WLTR", ctypes.c_double),
        ("CantTR", ctypes.c_double),
        ("OmegaTR", ctypes.c_double),
        ("CHRDTR", ctypes.c_double),
        ("RTR", ctypes.c_double),
        ("BTLTR", ctypes.c_double),
        ("a0TR", ctypes.c_double),
        ("IbTR", ctypes.c_double),
        ("twistTR", ctypes.c_double),
        ("BIASTR", ctypes.c_double),
        ("D0TR", ctypes.c_double),
        ("D1TR", ctypes.c_double),
        ("D2TR", ctypes.c_double),
        ("CDTR", ctypes.c_double),
        ("TD3TR", ctypes.c_double),
        ("DELTTR", ctypes.c_double),
        ("BVTTR", ctypes.c_double),
        ("BVTTR1", ctypes.c_double),
        ("VBVTTR", ctypes.c_double),
        ("STAIL", ctypes.c_double * 2),
        ("PHITAIL", ctypes.c_double * 2),
        ("ITAIL", ctypes.c_double * 2),
        ("FSTAIL", ctypes.c_double * 2),
        ("BLTAIL", ctypes.c_double * 2),
        ("WLTAIL", ctypes.c_double * 2),
        ("ALTAIL", ctypes.c_double * 50),
        ("CLTAIL", ctypes.c_double * 50),
        ("CDTAIL", ctypes.c_double * 50),
        ("CLELEV", ctypes.c_double * 2),
        ("STABSET", ctypes.c_double),
        ("LNKGAIN", ctypes.c_double * 16),
        ("MIXGAIN", ctypes.c_double * 16),
        ("TRGAIN", ctypes.c_double),
        ("TRBIAS", ctypes.c_double),
        ("SWASHGAIN", ctypes.c_double * 9),
        ("SWASHBIAS", ctypes.c_double * 3),
        ("a1f_tab", ctypes.c_double * 3),
        ("chi_tab", ctypes.c_double * 11),
        ("ekxf_tab", ctypes.c_double * 33),
        ("ekzf_tab", ctypes.c_double * 33),
        ("ekxt_tab", ctypes.c_double * 33),
        ("ekzt_tab", ctypes.c_double * 33),
        ("alpha_tab", ctypes.c_double * 8),
        ("qlossht_tab", ctypes.c_double * 8),
        ("psivt_tab", ctypes.c_double * 13),
        ("qlossvt_tab", ctypes.c_double * 13),
        ("alphaeps_tab", ctypes.c_double * 25),
        ("eps_tab", ctypes.c_double * 25),
        ("psisig_tab", ctypes.c_double * 25),
        ("sig_tab", ctypes.c_double * 25),
        ("HPMAX", ctypes.c_double),
        ("TauEng", ctypes.c_double),
        ("QEMax", ctypes.c_double),
        ("IDEALENG", ctypes.c_double),
        ("HPACC", ctypes.c_double),
        ("GEARENG", ctypes.c_double),
        ("GEARACC", ctypes.c_double),
        ("GEARTR", ctypes.c_double),
        ("JTR", ctypes.c_double),
        ("JAC", ctypes.c_double),
        ("JENG", ctypes.c_double),
        ("JMROT", ctypes.c_double),
        ("JGBX", ctypes.c_double),
        ("RPM2RPS", ctypes.c_double),
        ("GBXDAMP", ctypes.c_double),
        ("XSCALE", ctypes.c_double * 39),
        ("DELCLIN", ctypes.c_double * 4),
        ("DELXLIN", ctypes.c_double * 39),
        ("xp", ctypes.c_double),
        ("yp", ctypes.c_double),
        ("zp", ctypes.c_double),
        ("GroundZ", ctypes.c_double),
        ("dt", ctypes.c_double),
        ("IFREEZE", ctypes.c_double),
        ("FP_ITMAX", ctypes.c_double),
        ("FPTOL", ctypes.c_double),
        ("NREVSTEP", ctypes.c_double),
        ("NREVCONV", ctypes.c_double),
        ("NREVAVERAGE", ctypes.c_double),
        ("TRIMSTATE", ctypes.c_double * 8),
        ("TRIMCTRL", ctypes.c_double * 4),
        ("TRIMTARG", ctypes.c_double * 12),
        ("TRIMRELAX", ctypes.c_double),
        ("TRIMTOL", ctypes.c_double),
        ("TRIMITMAX", ctypes.c_double),
        ("TRIMJACTOL", ctypes.c_double),
    ]


class HeloModel:
    """Thin Python wrapper around the C helicopter model's shared library.

    """

    def __init__(self) -> None:
        self._lib = _load_library()
        self._handle = None  # opaque pointer returned by the C model, if any
        self._lib.InitFcnH60.argtypes = [
            ctypes.POINTER(FlightConditions),
            ctypes.c_double * NSTATES,
            ctypes.c_double * NCTRLS,
            ctypes.c_double * NSTATES,
            ctypes.c_double * NOUT,
            ctypes.POINTER(ctypes.c_double),
            ctypes.POINTER(Constants),
        ]
        self._lib.InitFcnH60.restype = None

        self._lib.StepH60.argtypes = [
            ctypes.c_double * NSTATES,
            ctypes.c_double * NCTRLS,
            ctypes.c_double * NSTATES,
            ctypes.c_double,
            ctypes.POINTER(Constants),
            ctypes.c_double * NSTATES,
            ctypes.c_double * NOUT,
            ctypes.c_double * NSTATES,
        ]
        self._lib.StepH60.restype = None

        self._x = (ctypes.c_double * NSTATES)()
        self._u = (ctypes.c_double * NCTRLS)()
        self._xdot = (ctypes.c_double * NSTATES)()
        self._xnew = (ctypes.c_double * NSTATES)()
        self._ynew = (ctypes.c_double * NOUT)()
        self._xdotnew = (ctypes.c_double * NSTATES)()
        self._constants = Constants()
        self._dt = 0.01  # overwritten from constants.dt after reset()

    def reset(self,flight_conditions:dict[str,float]) -> np.ndarray:

        fc = FlightConditions(**flight_conditions)
        itrim = ctypes.c_double()

        self._lib.InitFcnH60(
            ctypes.byref(fc),self._x, self._u, self._xdot, self._ynew,
            ctypes.byref(itrim), ctypes.byref(self._constants),
        )

        self._dt = self._constants.dt

        return np.ctypeslib.as_array(self._x).copy() #NOTE: This output should be whatever the
        # observation space is. Whether its all of x all of y or a subset.

    def step(self, action: np.ndarray) -> tuple[np.ndarray, np.ndarray]:
        """Advance one dt using StepH60. `action` must have length NCTRLS."""
        self._u[:] = action

        self._lib.StepH60(
            self._x, self._u, self._xdot, self._dt,
            ctypes.byref(self._constants),
            self._xnew, self._ynew, self._xdotnew,
        )

        # Roll state forward for the next call.
        self._x[:] = self._xnew
        self._xdot[:] = self._xdotnew

        next_state = np.ctypeslib.as_array(self._xnew).copy()
        outputs = np.ctypeslib.as_array(self._ynew).copy()

        
        return next_state, outputs