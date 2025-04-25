mkdir -p build
rm -f ./build/daxpy_performance.csv
g++ -std=c++17 -Iproblem1 -c daxpy_test.cpp -o ./build/daxpy_test.o
g++ -std=c++17 -Iproblem1 -c problem1/ref_daxpy.cpp -o ./build/ref_daxpy.o
g++ -o ./build/x_daxpy_test ./build/daxpy_test.o ./build/ref_daxpy.o
./build/x_daxpy_test && python ./scripts/plot_daxpy.py