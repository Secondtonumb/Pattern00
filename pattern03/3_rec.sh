#!/bin/bash

num=$1
for k in $(seq 1 ${num})
do
    ./pl_rec ./test_data/weight${k}.dat unknown.dat
done
