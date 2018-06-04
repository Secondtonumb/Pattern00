#!/bin/bash

num=$1
for k in $(seq 1 ${num})
do
    touch ./test_data/weight${k}.dat
    ./pl learning_data.list ./test_data/init_weight${k}.dat ./test_data/weight${k}.dat 1 >> make_weight.log
done
    
