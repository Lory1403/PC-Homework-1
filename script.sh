#!/bin/bash
# Author: Lorenzo Fasol

mkdir -p results

echo -e "\nArray addition and vectorization\n"

echo -e "--> Sequential routine1()\n"
g++ hw1_pt1.cpp -o hw1_pt1_sequential.out
./hw1_pt1_sequential.out -f results/hw1_pt1_sequential.csv
wait

echo -e "--> Implicit parallelism techniques on routine1()\n"
g++ hw1_pt1.cpp -O2 -ftree-vectorize -funroll-loops -fprefetch-loop-arrays -march=native -o hw1_pt1_parallel.out
./hw1_pt1_parallel.out -f results/hw1_pt1_parallel.csv
wait

echo -e "----------"

echo -e "\nMatrix copy via block reverse ordering\n"

echo -e "--> Sequential routine1()\n"
g++ hw1_pt2.cpp -o hw1_pt2_sequential.out
./hw1_pt2_sequential.out -f results/hw1_pt2_sequential.csv
wait

echo -e "--> Implicit parallelism techniques on routine1()\n"
g++ hw1_pt2.cpp -O2 -ftree-vectorize -funroll-loops -fprefetch-loop-arrays -march=native -o hw1_pt2_parallel.out
./hw1_pt2_parallel.out -f results/hw1_pt2_parallel.csv
wait
