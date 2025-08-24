
PROGRAM=/home/jayiuliano/repos/newtoollib/bin/linux/astro_exe
OUTFILE=/home/jayiuliano/repos/newtoollib/tests/profiling/results/callgrind.main

valgrind --tool=callgrind --callgrind-out-file=$OUTFILE $PROGRAM

callgrind_annotate --show-percs=yes --inclusive=yes $OUTFILE > $OUTFILE.inclusive
callgrind_annotate --show-percs=yes --inclusive=no $OUTFILE > $OUTFILE.exclusive