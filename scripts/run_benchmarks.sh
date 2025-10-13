#!/bin/bash

benchmark_files=$(find ./install -type f -path "**/benchmark/*")

for filepath in $benchmark_files; do
    file=$(basename "$filepath")
    echo "\n----------------------------------------"
    echo "----------------------------------------"
    echo "Running benchmark: $file"
    echo "----------------------------------------"
    echo "----------------------------------------\n"
    eval "$filepath --benchmark_dry_run=false --benchmark_repetitions=10 --benchmark_report_aggregates_only=true --benchmark_time_unit=s --benchmark_out=.benchmark"
done
echo "\n"