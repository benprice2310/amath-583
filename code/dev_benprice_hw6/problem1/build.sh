# remove files
rm -rf arc_length scaling.csv error.csv 

# compile the code
g++  -O3 -std=c++17 -pthread arc_length.cpp -o arc_length

