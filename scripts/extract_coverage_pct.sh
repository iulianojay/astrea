#!/bin/bash

coverage_line=$(<.gcovr/coverage.xml grep -Poahr 'coverage line-rate="(0.[0-9]{0,})"')
echo "$coverage_line"

re="(0.[0-9]+)"
if [[ $coverage_line =~ $re ]]; then 
    coverage_value=${BASH_REMATCH[1]}; 
else
    echo "Regex match failed"
    exit 1
fi
echo "Extracted coverage value: $coverage_value"

coverage_pct=${coverage_value:2:2}.${coverage_value:4:2}
echo "Formatted coverage percentage: $coverage_pct"

export COVERAGE_PCT=$coverage_pct