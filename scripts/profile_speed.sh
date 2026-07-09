
PROGRAM_NAME=hermes
DEBUG=RelWithDebInfo
PROGRAM=./install/gcc/gcc-15-23/$DEBUG/bin/$PROGRAM_NAME/$PROGRAM_NAME
BASE_DIR=./astrea/hermes/results/profiling
OUTFILE=$BASE_DIR/callgrind.out
# PROGRAM=./astrea/astro/tests/profiling/bin/astro_profiler
# OUTFILE=./astrea/astro/tests/profiling/results/callgrind.out

######################################
## ----- Valgrind / Callgrind ----- ##
######################################

OPTIONS="--callgrind-out-file=$OUTFILE --dump-instr=yes --collect-jumps=yes"
CALLGRIND_CMD="valgrind --tool=callgrind $OPTIONS $PROGRAM"

echo $CALLGRIND_CMD
# eval $CALLGRIND_CMD

CALLGRIND_OPTIONS="--threshold=100 --tree=both"
ANNOTATE_INCLUSIVE_CMD="callgrind_annotate $CALLGRIND_OPTIONS --inclusive=yes $OUTFILE  > $OUTFILE.inclusive"
ANNOTATE_EXCLUSIVE_CMD="callgrind_annotate $CALLGRIND_OPTIONS --inclusive=no $OUTFILE  > $OUTFILE.exclusive"

echo $ANNOTATE_INCLUSIVE_CMD
eval $ANNOTATE_INCLUSIVE_CMD

echo $ANNOTATE_EXCLUSIVE_CMD
eval $ANNOTATE_EXCLUSIVE_CMD

########################################
## ----- Gprof Graph Generation ----- ##
########################################

# Exclusive graph
GRAPH_OUTFILE=$BASE_DIR/callgrind
VENV_CMD=". ./.venv/bin/activate"
GPROF_OPTIONS="--format=callgrind $OUTFILE"

GPROF_EXCLUSIVE_CMD="python3 -m gprof2dot --color-nodes-by-selftime --output=$GRAPH_OUTFILE.exclusive.dot $GPROF_OPTIONS"
GPROF_INCLUSIVE_CMD="python3 -m gprof2dot --output=$GRAPH_OUTFILE.inclusive.dot $GPROF_OPTIONS"

echo $GPROF_EXCLUSIVE_CMD
eval "$VENV_CMD && $GPROF_EXCLUSIVE_CMD"

echo $GPROF_INCLUSIVE_CMD
eval "$VENV_CMD && $GPROF_INCLUSIVE_CMD"

DOT_EXCLUSIVE_CMD="dot -Tpng $GRAPH_OUTFILE.exclusive.dot -o $BASE_DIR/exclusive.png"
DOT_INCLUSIVE_CMD="dot -Tpng $GRAPH_OUTFILE.inclusive.dot -o $BASE_DIR/inclusive.png"

echo $DOT_EXCLUSIVE_CMD
eval $DOT_EXCLUSIVE_CMD

echo $DOT_INCLUSIVE_CMD
eval $DOT_INCLUSIVE_CMD
