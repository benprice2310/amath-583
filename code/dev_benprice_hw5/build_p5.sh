#!/bin/sh

cd ./problem5

rm strassen_test strassen_perf.csv

g++ -std=c++14 -O3 strassen.cpp strassen_test.cpp -o strassen_test
./strassen_test > strassen_perf.csv
echo "compiled and ran strassen_test"

echo "strassen_perf.csv file created"

python plot_timings.py
echo "strassen_perf.csv file plotted"

cd ../
