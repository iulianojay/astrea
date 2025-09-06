
OUTFILE=.coverage.info
OUTDIR=.coverage

eval "lcov --directory ./build/ --capture --output-file $OUTFILE -rc lcov_branch_coverage=1"
eval "lcov -r $OUTFILE "*/usr/*" -o $OUTFILE"
eval "lcov -r $OUTFILE "*/extern/*" -o $OUTFILE"
eval "lcov -r $OUTFILE "*/.conan2/*" -o $OUTFILE"
eval "lcov -r $OUTFILE "*mp-units*" -o $OUTFILE"
eval "lcov -r $OUTFILE "*googletest*" -o $OUTFILE"

eval "genhtml $OUTFILE --prefix $ASTREA_ROOT --output-directory $OUTDIR"