#!/bin/bash

example_files=$(find ./astrea -type f -path "**/bin/*")

for filepath in $example_files; do
    file=$(basename "$filepath")
    echo "\n----------------------------------------"
    echo "----------------------------------------"
    echo "Running example: $file"
    echo "----------------------------------------"
    echo "----------------------------------------\n"
    eval "$filepath"
done
echo "\n"