#!/bin/zsh

# Timestamped folder name
timestamp=$(date +%Y%m%d_%H%M%S)
trial_dir="build/trial_$timestamp"
mkdir -p "$trial_dir"

echo "▶️ Running DAXPY performance test → $trial_dir"

# Build step
g++ -std=c++17 -Iproblem1 -c daxpy_test.cpp -o "$trial_dir/daxpy_test.o"
g++ -std=c++17 -Iproblem1 -c problem1/ref_daxpy.cpp -o "$trial_dir/ref_daxpy.o"
g++ -o "$trial_dir/x_daxpy_test" "$trial_dir/daxpy_test.o" "$trial_dir/ref_daxpy.o"

# Run performance test and output CSV inside trial directory
"$trial_dir/x_daxpy_test" "$trial_dir/daxpy_performance.csv"

# Check if plotting script exists
if [ ! -f "scripts/plot_daxpy.py" ]; then
    echo "❌ Plotting script not found: scripts/plot_daxpy.py"
    exit 1
fi

# Generate performance plot
python3 "scripts/plot_daxpy.py" "$trial_dir/daxpy_performance.csv" "$trial_dir/daxpy_performance_plot.png"

echo "✅ Output saved to $trial_dir/"