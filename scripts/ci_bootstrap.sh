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

# Ensure uv is available. Prefer an existing binary; otherwise bootstrap via pip.
if ! command -v uv >/dev/null 2>&1; then
  "${py_bin}" -m pip install --user uv
fi

uv_user_bin="$(${py_bin} - <<'PY'
import os
import site
print(os.path.join(site.USER_BASE, "bin"))
PY
)"
uv_user_scripts="$(${py_bin} - <<'PY'
import os
import site
print(os.path.join(site.USER_BASE, "Scripts"))
PY
)"
export PATH="${uv_user_bin}:${uv_user_scripts}:$PATH"

uv venv .venv --python "${py_bin}"

# MSYS2 and Unix-like shells both use bin/activate for venv activation.
# shellcheck disable=SC1091
source .venv/bin/activate

# Install only CI tooling; do not install repository root as a Python package.
uv pip install "cmake>=4.3.2" conan numpy

# Only coverage jobs need gcovr. Installing it on MSYS2 can require extra
# native XML deps, so keep it opt-in.
if [[ "${CI_INSTALL_GCOVR:-0}" == "1" ]]; then
  uv pip install gcovr
fi

python --version
uv --version
conan --version
