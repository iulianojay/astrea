#!/usr/bin/env bash

set -euo pipefail

script_dir="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
repo_root="$(cd -- "$script_dir/.." && pwd)"
data_file="$repo_root/astrea/astro/data/space_weather/SpaceWeather-All-v1.2.txt"
download_url="https://gitlab.orekit.org/orekit/orekit-data/-/raw/main/CSSI-Space-Weather-Data/SpaceWeather-All-v1.2.txt"
tmp_file="$(mktemp "${data_file}.XXXXXX")"

trap 'rm -f "$tmp_file"' EXIT

echo "Downloading CSSI space weather data from the Orekit data repository..."
curl --fail --location --show-error --progress-bar \
    --connect-timeout 15 --max-time 300 --retry 2 \
    "$download_url" --output "$tmp_file"

if ! grep -qE '^DATATYPE[[:space:]]+CssiSpaceWeather$' "$tmp_file" ||
    ! grep -qE '^VERSION[[:space:]]+1\.2([[:space:]]|$)' "$tmp_file" ||
    ! grep -qE '^[[:space:]]*[0-9]{4}[[:space:]]+[0-9]{2}[[:space:]]+[0-9]{2}[[:space:]]' "$tmp_file"; then
    echo "Downloaded file is not valid CelesTrak CSSI Space Weather data." >&2
    exit 1
fi

chmod 0644 "$tmp_file"
mv -- "$tmp_file" "$data_file"

echo "Updated $data_file"
