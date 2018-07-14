sam_num=100
PTN=ptns.dat
REC=rec.dat
SAMPLES=resamp.dat
FOREST=forest.dat
W_FOREST=new_forest.dat
ADABOOST_LOG=ada.log
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

gcc -o sampling sampling.c
gcc -o adaboost adaboost.c
gcc -o strong strong.c

echo "Compilation  Completed"

./sampling ${PTN} ${SAMPLES} ${sam_num}
./adaboost ${SAMPLES} ${FOREST} ${W_FOREST} > ${ADABOOST_LOG}
./strong ${REC} ${W_FOREST}

echo "Finished"
