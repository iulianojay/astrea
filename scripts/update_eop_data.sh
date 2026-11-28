#!/usr/bin/env bash

set -euo pipefail

script_dir="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
repo_root="$(cd -- "$script_dir/.." && pwd)"
data_dir="$repo_root/astrea/astro/data/earth_orientation_parameters"
base_url="https://eop2-external.jpl.nasa.gov/eop2"
curl_opts=(--fail --location --show-error --connect-timeout 15 --max-time 300 --retry 2)

tmp_long="$(mktemp "$data_dir/eop.long.XXXXXX")"
tmp_short="$(mktemp "$data_dir/eop.short.XXXXXX")"
trap 'rm -f "$tmp_long" "$tmp_short"' EXIT

# JPL publishes one dated release per day (YYMMDD_HHMMSS-marge_eop2.{long,short}); pick the newest.
echo "Finding the latest JPL EOP2 release..."
release="$(
    curl --silent "${curl_opts[@]}" "$base_url/" |
        grep -oE '[0-9]{6}_[0-9]{6}-marge_eop2\.long' |
        sort -u |
        tail -n 1
)"
if [[ -z "$release" ]]; then
    echo "No EOP2 release found at $base_url/." >&2
    exit 1
fi
release="${release%.long}"

echo "Downloading JPL EOP2 release $release..."
curl --progress-bar "${curl_opts[@]}" "$base_url/$release.long" --output "$tmp_long"
curl --progress-bar "${curl_opts[@]}" "$base_url/$release.short" --output "$tmp_short"

# eop_parser.py skips a fixed 20-line header, so the data must start right after the 'EOP2=' line 20.
for file in "$tmp_long" "$tmp_short"; do
    if ! head -n 1 "$file" | grep -qF 'JPL Earth Orientation Parameter 2 (EOP2) File' ||
        [[ "$(sed -n '20p' "$file")" != ' EOP2=' ]] ||
        ! sed -n '21p' "$file" | grep -qE '^ *[0-9]+\.[0-9]+,' ||
        [[ "$(tail -n 1 "$file")" != ' $END' ]]; then
        echo "Downloaded file is not valid JPL EOP2 data in the expected layout." >&2
        exit 1
    fi
done

chmod 0644 "$tmp_long" "$tmp_short"
mv -- "$tmp_long" "$data_dir/eop.long"
mv -- "$tmp_short" "$data_dir/eop.short"

sed -n '2,3p' "$data_dir/eop.long" | sed 's/^ \$ */  /'
echo "Updated $data_dir/eop.long and eop.short"
