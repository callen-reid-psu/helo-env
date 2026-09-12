#!/usr/bin/env bash
#
# import_coder_output.sh
#
# Imports MATLAB Coder generated C code into the HeloEnv native/ layout.
#
#   - Copies all *.c / *.cpp files  -> src/helo_env/native/src/
#   - Copies all *.h / *.hpp files  -> src/helo_env/native/include/
#   - Attempts to locate tmwtypes.h from the local MATLAB install and
#     copies it into native/include/ as well.
#
# Usage:
#   ./scripts/import_coder_output.sh <path-to-matlab-coder-output-dir> [matlab-root]
#
# Example:
#   ./scripts/import_coder_output.sh ~/matlab/MyModel_ert_rtw
#   ./scripts/import_coder_output.sh ~/matlab/MyModel_ert_rtw /usr/local/MATLAB/R2024a
#
set -euo pipefail

# ---------------------------------------------------------------------------
# Args / sanity checks
# ---------------------------------------------------------------------------
if [[ $# -lt 1 ]]; then
    echo "Usage: $0 <path-to-matlab-coder-output-dir> [matlab-root]" >&2
    exit 1
fi

CODER_DIR="$1"
MATLAB_ROOT_OVERRIDE="${2:-}"

if [[ ! -d "$CODER_DIR" ]]; then
    echo "Error: coder output directory not found: $CODER_DIR" >&2
    exit 1
fi

# ---------------------------------------------------------------------------
# Resolve project paths (this script is expected to live in <repo>/scripts/)
# ---------------------------------------------------------------------------
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"

NATIVE_DIR="$PROJECT_ROOT/src/helo_env/native"
SRC_DEST="$NATIVE_DIR/src"
INCLUDE_DEST="$NATIVE_DIR/include"

mkdir -p "$SRC_DEST" "$INCLUDE_DEST"

echo "Project root : $PROJECT_ROOT"
echo "Coder output : $CODER_DIR"
echo "Dest src     : $SRC_DEST"
echo "Dest include : $INCLUDE_DEST"
echo

# ---------------------------------------------------------------------------
# Copy source files
# ---------------------------------------------------------------------------
copy_matches() {
    local pattern="$1"
    local dest="$2"
    local count=0

    while IFS= read -r -d '' file; do
        cp -v "$file" "$dest/"
        count=$((count + 1))
    done < <(find "$CODER_DIR" -type f -iname "$pattern" -print0)

    echo "Copied $count file(s) matching '$pattern' to $dest"
}

echo "== Copying .c/.cpp files =="
copy_matches "*.c" "$SRC_DEST"
copy_matches "*.cpp" "$SRC_DEST"
echo

echo "== Copying .h/.hpp files =="
copy_matches "*.h" "$INCLUDE_DEST"
copy_matches "*.hpp" "$INCLUDE_DEST"
echo

# ---------------------------------------------------------------------------
# Locate MATLAB root
# ---------------------------------------------------------------------------
find_matlab_root() {
    # 1. Explicit override wins
    if [[ -n "$MATLAB_ROOT_OVERRIDE" ]]; then
        echo "$MATLAB_ROOT_OVERRIDE"
        return 0
    fi

    # 2. Environment variable, if already set
    if [[ -n "${MATLAB_ROOT:-}" ]]; then
        echo "$MATLAB_ROOT"
        return 0
    fi

    # 3. Ask MATLAB itself, if it's on PATH
    if command -v matlab >/dev/null 2>&1; then
        local root
        root="$(matlab -batch "disp(matlabroot)" 2>/dev/null | tail -n 1 | tr -d '\r')"
        if [[ -n "$root" && -d "$root" ]]; then
            echo "$root"
            return 0
        fi
    fi

    # 4. Search common install locations by platform
    local candidates=()
    case "$(uname -s)" in
        Darwin)
            candidates=(/Applications/MATLAB_R*.app)
            ;;
        Linux)
            candidates=(/usr/local/MATLAB/R* /opt/MATLAB/R*)
            ;;
        MINGW*|MSYS*|CYGWIN*)
            candidates=("/c/Program Files/MATLAB/R"*)
            ;;
    esac

    local latest=""
    for c in "${candidates[@]}"; do
        [[ -d "$c" ]] || continue
        latest="$c"  # relies on glob sort order; last match = newest release string
    done

    if [[ -n "$latest" ]]; then
        echo "$latest"
        return 0
    fi

    return 1
}

echo "== Locating tmwtypes.h =="
MATLAB_ROOT_FOUND=""
if MATLAB_ROOT_FOUND="$(find_matlab_root)"; then
    echo "MATLAB root candidate: $MATLAB_ROOT_FOUND"
    TMWTYPES_PATH="$MATLAB_ROOT_FOUND/extern/include/tmwtypes.h"
    if [[ -f "$TMWTYPES_PATH" ]]; then
        cp -v "$TMWTYPES_PATH" "$INCLUDE_DEST/"
        echo "tmwtypes.h copied from MATLAB install."
    else
        echo "Warning: MATLAB root found but tmwtypes.h not at expected path: $TMWTYPES_PATH"
    fi
else
    echo "MATLAB installation not found automatically."
fi

# Fallback: sometimes tmwtypes.h ships alongside the coder output itself
if [[ ! -f "$INCLUDE_DEST/tmwtypes.h" ]]; then
    FOUND_LOCAL="$(find "$CODER_DIR" -type f -iname "tmwtypes.h" -print -quit)"
    if [[ -n "$FOUND_LOCAL" ]]; then
        cp -v "$FOUND_LOCAL" "$INCLUDE_DEST/"
        echo "tmwtypes.h copied from coder output directory."
    fi
fi

if [[ ! -f "$INCLUDE_DEST/tmwtypes.h" ]]; then
    cat >&2 <<'EOF'

WARNING: tmwtypes.h could not be located automatically.
You can supply the MATLAB root manually, e.g.:

    ./scripts/import_coder_output.sh <coder_dir> "/usr/local/MATLAB/R2024a"

or copy it in yourself from <matlabroot>/extern/include/tmwtypes.h
EOF
fi

echo
echo "Done. Review $SRC_DEST and $INCLUDE_DEST, then update native/CMakeLists.txt if needed."
