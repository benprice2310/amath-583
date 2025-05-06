#!/bin/zsh

echo "▶️ Compiling object files into problem5/ ..."

g++ -c -fPIC problem1/ref_daxpy.cpp -o problem5/ref_daxpy.o
g++ -c -fPIC problem2/ref_dgemv.cpp -o problem5/ref_dgemv.o
g++ -c -fPIC problem3/ref_dgemm.cpp -o problem5/ref_dgemm.o

echo "✅ Object files compiled."

echo "▶️ Creating shared library librefBLAS.so inside problem5/..."
g++ -shared -o problem5/librefBLAS.so problem5/ref_daxpy.o problem5/ref_dgemv.o problem5/ref_dgemm.o

echo "✅ librefBLAS.so created."

echo "▶️ Compiling and linking test_refBLAS.cpp ..."

g++ -std=c++17 -I. -Iproblem5 -Lproblem5 problem5/test_refBLAS.cpp -lrefBLAS -o problem5/xrefBLAS_test

echo "✅ Test executable created at problem5/xrefBLAS_test."

echo "▶️ Running test program..."
./problem5/xrefBLAS_test

echo "✅ Test complete."