#!/bin/zsh

echo "▶️ Building and running template test..."

mkdir -p build/template_test

# Build
g++ -std=c++17 -Iproblem4 -o build/template_test/x_template_test dblas_template_test.cpp

# Run
./build/template_test/x_template_test

echo "✅ Template test complete."