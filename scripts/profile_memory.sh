
DEBUG=RelWithDebInfo
PROGRAM=./install/gcc-13-23/$DEBUG/bin/trace/trace
OUTFILE=./astrea/trace/trace/drivers/results/massif.out

OPTIONS="--massif-out-file=$OUTFILE --time-unit=B"
MASSIF_CMD="valgrind --tool=massif $OPTIONS $PROGRAM"

echo $MASSIF_CMD
eval $MASSIF_CMD

MS_PRINT_CMD="ms_print $OUTFILE 2>&1 | tee $OUTFILE.print"

echo $MS_PRINT_CMD
eval $MS_PRINT_CMD