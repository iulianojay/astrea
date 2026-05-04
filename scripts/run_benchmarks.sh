#!/bin/bash

benchmark_files=$(find ./install/** -type f -path "**/benchmarks/*.benchmark")

for filepath in $benchmark_files; do
    file=$(basename "$filepath")
    dir=$(dirname "$filepath")
    mkdir -p "$dir/benchmark_results"
    echo "\n----------------------------------------"
    echo "----------------------------------------"
    echo "Running benchmark: $file"
    echo "----------------------------------------"
    echo "----------------------------------------\n"
    eval "$filepath --benchmark_out_format=json --benchmark_out=$dir/benchmark_results/$file.json" > /dev/null
    echo "Benchmark $file completed. Results saved to $dir/benchmark_results/$file.json \n"
done
echo "\n"

python3 "$(dirname "$0")/print_benchmark_results.py"