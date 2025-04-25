clear
ls -lstr code/learning
g++ -std=c++17 -c code/learning/cpp-types.cpp -o code/learning/cpp-types.o
ls -lstr code/learning
g++ -o code/learning/xcpp-types code/learning/cpp-types.o
ls -lstr code/learning
./code/learning/xcpp-types
