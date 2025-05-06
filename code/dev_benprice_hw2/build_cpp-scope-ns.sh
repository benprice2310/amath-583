clear
ls -lstr code/learning
g++ -std=c++17 -c code/learning/cpp-scope-ns.cpp -o code/learning/cpp-scope-ns.o
ls -lstr code/learning
g++ -o code/learning/xcpp-scope-ns code/learning/cpp-scope-ns.o
ls -lstr code/learning
./code/learning/xcpp-scope-ns
