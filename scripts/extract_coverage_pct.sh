#!/bin/bash
set -euo pipefail

if [[ ! -f .gcovr/coverage.xml ]]; then
    echo "coverage.xml not found"
    exit 1
fi

coverage_value=$(grep -Eo 'line-rate="[0-9]+(\.[0-9]+)?"' .gcovr/coverage.xml | head -n1 | cut -d'"' -f2)

if [[ -z "${coverage_value}" ]]; then
    echo "Regex match failed"
    exit 1
fi

coverage_pct=$(awk -v v="$coverage_value" 'BEGIN { printf "%.2f", v * 100 }')
echo "Extracted coverage value: $coverage_value"
echo "Formatted coverage percentage: $coverage_pct"

echo -n "$coverage_pct" >> coverage.txt