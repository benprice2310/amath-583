#!/bin/zsh

# Timestamped folder name
timestamp=$(date +%Y%m%d_%H%M%S)
trial_dir="build/dgemm_trial_$timestamp"
mkdir -p "$trial_dir"

echo "▶️ Running DGEMM performance test → $trial_dir"

# Build
g++ -std=c++17 -Iproblem3 -c dgemm_test.cpp -o "$trial_dir/dgemm_test.o"
g++ -std=c++17 -Iproblem3 -c problem3/ref_dgemm.cpp -o "$trial_dir/ref_dgemm.o"
g++ -o "$trial_dir/x_dgemm_test" "$trial_dir/dgemm_test.o" "$trial_dir/ref_dgemm.o"

# Run
"$trial_dir/x_dgemm_test" "$trial_dir/dgemm_performance.csv"

# Check if plot script exists
if [ ! -f "scripts/plot_dgemm.py" ]; then
    echo "❌ Plotting script not found: scripts/plot_dgemm.py"
    exit 1
fi

# Plot
python3 "scripts/plot_dgemm.py" "$trial_dir/dgemm_performance.csv" "$trial_dir/dgemm_performance_plot.png"

echo "✅ Output saved to $trial_dir/"