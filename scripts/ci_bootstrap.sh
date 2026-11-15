#!/usr/bin/env bash
set -euo pipefail

# Allow overriding the interpreter, otherwise prefer python3 when available.
if [[ -n "${PYTHON_BIN:-}" ]]; then
  py_bin="${PYTHON_BIN}"
elif command -v python3 >/dev/null 2>&1; then
  py_bin="python3"
else
  py_bin="python"
fi

"${py_bin}" -m venv .venv

# MSYS2 and Unix-like shells both use bin/activate for venv activation.
# shellcheck disable=SC1091
source .venv/bin/activate

# GitHub container runners often mount a non-writable default pip cache path.
export PIP_NO_CACHE_DIR=1

python -m pip install --upgrade pip setuptools wheel

# Install only CI tooling; do not install repository root as a Python package.
pip install "cmake>=4.3.2" conan

# Only coverage jobs need gcovr. Installing it on MSYS2 can require extra
# native XML deps, so keep it opt-in.
if [[ "${CI_INSTALL_GCOVR:-0}" == "1" ]]; then
  pip install gcovr
fi

python --version
pip --version
conan --version
