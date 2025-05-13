#!/bin/sh

cd ./problem3

rm mem_swaps_test timings.csv
g++ -std=c++14 mem_swaps_test.cpp -o mem_swaps_test
./mem_swaps_test > timings.csv

echo "compiled and ran mem_swaps_test"
echo "timings.csv file created"

python plot_timings.py
echo "timings.csv file plotted"

cd ../
