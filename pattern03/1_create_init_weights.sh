#!/bin/bash

num=$1
for k in $(seq 1 ${num})
do
    echo "create init_weight${k}.dat"
    touch ./test_data/init_weight${k}.dat
    python make_init_weight.py ./test_data/init_weight${k}.dat
    head ./test_data/init_weight${k}.dat
done    


