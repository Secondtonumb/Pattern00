#!/bin/bash

num=$1
./1_create_init_weights.sh ${num}

./2_create_weights.sh ${num}

./3_rec.sh ${num}| grep "recog result" |sort > recog_result


