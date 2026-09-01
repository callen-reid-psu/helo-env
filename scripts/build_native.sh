#!/usr/bin/env bash
# Configures and builds the C helicopter model into a shared library
# consumed by src/helo_env/native/bindings.py.
set -euo pipefail

NATIVE_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)/src/helo_env/native"
BUILD_DIR="${NATIVE_DIR}/cmake-build"

mkdir -p "${BUILD_DIR}"
cmake -S "${NATIVE_DIR}" -B "${BUILD_DIR}" -DCMAKE_BUILD_TYPE=Release
cmake --build "${BUILD_DIR}" --config Release

echo "Native library built into: ${NATIVE_DIR}/build"
