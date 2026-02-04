
OUTFILE=.coverage.info
OUTDIR=.coverage

# Run lcov to gather coverage data
THIS_DIR=$(dirname -- "$0")
ASTREA_ROOT=$(realpath "$THIS_DIR/..")

eval "cd $ASTREA_ROOT"
eval "lcov --directory ./build/ --capture --output-file $OUTFILE -rc lcov_branch_coverage=1"

# Remove external dependencies
eval "lcov -r $OUTFILE "*/usr/*" -o $OUTFILE"
eval "lcov -r $OUTFILE "*/extern/*" -o $OUTFILE"
eval "lcov -r $OUTFILE "*mp-units*" -o $OUTFILE"
eval "lcov -r $OUTFILE "*googletest*" -o $OUTFILE"

# Remove test files
eval "lcov -r $OUTFILE "*.test.cpp*" -o $OUTFILE"
eval "lcov -r $OUTFILE "*driver.cpp*" -o $OUTFILE"
eval "lcov -r $OUTFILE "*test_util.hpp*" -o $OUTFILE"
eval "lcov -r $OUTFILE "*tests/utilities/*" -o $OUTFILE"

# Generate HTML report
eval "genhtml $OUTFILE --prefix $ASTREA_ROOT --output-directory $OUTDIR"