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

if ! command -v uv >/dev/null 2>&1; then
  if command -v curl >/dev/null 2>&1; then
    curl -LsSf https://astral.sh/uv/install.sh | sh
    export PATH="$HOME/.local/bin:$PATH"
  else
    echo "uv is not available in PATH and curl is missing; cannot install uv automatically."
    exit 1
  fi
fi

uv venv .venv --python "${py_bin}"

# Activate virtualenv across Unix and Windows/MSYS2 layouts.
if [[ -f .venv/bin/activate ]]; then
  # shellcheck disable=SC1091
  source .venv/bin/activate
elif [[ -f .venv/Scripts/activate ]]; then
  # shellcheck disable=SC1091
  source .venv/Scripts/activate
else
  echo "Unable to find a virtualenv activation script in .venv."
  exit 1
fi

# Sync project dependencies without attempting to install the repository itself
# as a Python package (this repo is not laid out as an installable package).
sync_args=(sync --no-install-project)

# Coverage-only dependencies are opted in via dependency groups.
if [[ "${CI_INSTALL_GCOVR:-0}" == "1" ]]; then
  sync_args+=(--group coverage)
fi

uv "${sync_args[@]}"

python --version
uv --version
conan --version
