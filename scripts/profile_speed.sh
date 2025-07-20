
DEBUG=RelWithDebInfo
PROGRAM=./install/x86_64-Linux/GNU-13.1.0/$DEBUG/access/bin/access
OUTFILE=./waveguide/access/access/drivers/results/callgrind.out

OPTIONS="--callgrind-out-file=$OUTFILE --dump-instr=yes --collect-jumps=yes"
CALLGRIND_CMD="valgrind --tool=callgrind $OPTIONS $PROGRAM"

echo $CALLGRIND_CMD
eval $CALLGRIND_CMD

CALLGRIND_OPTIONS="--threshold=100 --tree=both"
ANNOTATE_INCLUSIVE_CMD="callgrind_annotate $CALLGRIND_OPTIONS --inclusive=yes $OUTFILE  > $OUTFILE.inclusive"
ANNOTATE_EXCLUSIVE_CMD="callgrind_annotate $CALLGRIND_OPTIONS --inclusive=no $OUTFILE  > $OUTFILE.exclusive"

echo $ANNOTATE_INCLUSIVE_CMD
eval $ANNOTATE_INCLUSIVE_CMD
echo $ANNOTATE_EXCLUSIVE_CMD
eval $ANNOTATE_EXCLUSIVE_CMD