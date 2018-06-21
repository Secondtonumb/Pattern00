ROOT="${PWD}"
TRAIN_ROOT="${ROOT}/exp/train"
TEST_ROOT="${ROOT}/exp/test"
P_LST="p.list"
W_LST="w.list"
B_FILE="bias.dat"
TRAIN_LOG="${ROOT}/log.csv"

echo "Step0: Data Preparation"

cd ${TRAIN_ROOT}

ls ${TRAIN_ROOT}/ptns/* > ${P_LST}
ls ${TRAIN_ROOT}/weights/* > ${W_LST}

cd ${TEST_ROOT}

ls ${TEST_ROOT}/ptns/* > ${P_LST}

cp ${TRAIN_ROOT}/weights/* ${TEST_ROOT}/weights/
ls ${TEST_ROOT}/weights/* > ${W_LST}

cd ${ROOT}

echo  "Step1: Compile"

gcc -o nw nw.c

echo "Training Module Complie Complete"

gcc -o rec rec.c

echo "Recognition Module Complie Complete"

echo "Step2: Training"

./nw ${TRAIN_ROOT}/${P_LST} ${TRAIN_ROOT}/${B_FILE} ${TRAIN_ROOT}/${W_LST} ${TEST_ROOT}/${W_LST} ${TEST_ROOT}/${B_FILE} $1 > ${TRAIN_LOG}

FN=$(wc -l < ${TRAIN_ROOT}/${P_LST})

python plot.py $FN
