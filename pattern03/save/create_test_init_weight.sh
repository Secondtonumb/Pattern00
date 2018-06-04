#!/bin/bash

num=$1
for k in $(seq 1 ${num})
do
    echo "create init_weight${k}.dat"
    touch ./test_data/init_weight${k}.dat
    python make_weight.py ./test_data/init_weight${k}.dat
done    


