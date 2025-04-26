Problem 5 - Shared Object Library Instructions

(All commands are executed from the project root directory.)

1. Compile the object files:
g++ -c -fPIC problem1/ref_daxpy.cpp -o problem5/ref_daxpy.o
g++ -c -fPIC problem2/ref_dgemv.cpp -o problem5/ref_dgemv.o
g++ -c -fPIC problem3/ref_dgemm.cpp -o problem5/ref_dgemm.o

2. Create the shared object library:
g++ -shared -o problem5/librefBLAS.so problem5/ref_daxpy.o problem5/ref_dgemv.o problem5/ref_dgemm.o

3. Compile the test program:
g++ -std=c++17 -I. -Iproblem5 -Lproblem5 problem5/test_refBLAS.cpp -lrefBLAS -o problem5/xrefBLAS_test

4. Run the test program:
./problem5/xrefBLAS_test

--- ALTERNATIVE (UNIX) ---
user@device root % zsh build_sol.zsh

- OR - 

user@device root % chmod +x build_sol.zsh
user@device root % build_sol.zsh