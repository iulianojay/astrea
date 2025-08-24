
DEBUG=Debug
PROGRAM=./install/x86_64-Linux/GNU-13.1.0/$DEBUG/access/bin/access
OUTFILE=./astrea/access/access/drivers/results/valgrind.out

OPTIONS="--leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=$OUTFILE"
VALGRIND_CMD="valgrind $OPTIONS $PROGRAM"

echo $VALGRIND_CMD
eval $VALGRIND_CMD