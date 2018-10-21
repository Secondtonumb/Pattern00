#!/bin/bash
ROOT="${PWD}"
TRAIN_ROOT="${ROOT}/exp/train"
TEST_ROOT="${ROOT}/exp/test"
P_LST="p.list"
W_LST="w.list"
B_FILE="bias.dat"
TRAIN_LOG="${ROOT}/log.csv"

echo "Step0: Data Preparation"

cd ${TRAIN_ROOT}

ls ${TRAIN_ROOT}/ptns/*.dat > ${P_LST}
ls ${TRAIN_ROOT}/weights/*.dat > ${W_LST}

cd ${TEST_ROOT}

ls ${TEST_ROOT}/ptns/*.dat > ${P_LST}

cp ${TRAIN_ROOT}/weights/*.dat ${TEST_ROOT}/weights/
ls ${TEST_ROOT}/weights/*.dat > ${W_LST}

cd ${ROOT}
     			 
echo  "Step1: Compile"


    gcc -o nw nw.c -lm
    echo "Training Module Complie Complete"

    gcc -o rec rec.c -lm
    echo "Recognition Module Complie Complete"

echo "Step2: Training"

./nw sort_iris_train.dat  \
     ${TRAIN_ROOT}/${B_FILE} \
     ${TRAIN_ROOT}/${W_LST}  \
     ${TEST_ROOT}/${B_FILE}  \
     ${TEST_ROOT}/${W_LST}   \
     ${TRAIN_LOG}

echo "Step3: Recognition"

./rec iris_test.dat  \
      ${TEST_ROOT}/${B_FILE} \
      ${TEST_ROOT}/${W_LST}



