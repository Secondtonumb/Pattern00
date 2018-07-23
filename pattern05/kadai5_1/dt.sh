PTN=ptns.dat
REC=rec.dat
FOREST=forest.dat

# if[ ! -f ~/cart.c ]
# then echo "Source Code Not Found"
#      exit
# fi

# if[ ! -f ${PTN} ]; then
#     echo "Patterns Not Found"
#     exit
# fi

# if[ ! -f ${FOREST} ]; then
#     echo "Patterns Not Found"
#     exit
# fi

# if[ ! -f ${REC} ]; then
#     echo "Patterns Not Found"
#     exit
# fi

gcc -o cart cart.c
gcc -o rec rec.c

echo "Compilation  Completed"

./cart ${PTN} ${FOREST}
./rec ${REC} ${FOREST}

echo "Finished"
