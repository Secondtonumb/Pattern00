W_FOREST=$1

gcc -o plot plot.c

./plot grid.dat ${W_FOREST} > label.dat

cat label.dat| sed 's/ /,/g' | sed 's/,$//g' > label.csv

python plot.py
