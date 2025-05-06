clear;
ls -lstr code/hw2;
g++ -std=c++14 -c code/hw2/main.cpp -o code/hw2/main.o;
g++ -o code/hw2/xmain code/hw2/main.o;
ls -lstr code/hw2;
./code/hw2/xmain;