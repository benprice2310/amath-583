 #!/bin/zsh

# Timestamped folder name
timestamp=$(date +%Y%m%d_%H%M%S)
trial_dir="build/dgemv_trial_$timestamp"
mkdir -p "$trial_dir"

echo "▶️ Running DGEMV performance test → $trial_dir"

# Build
g++ -std=c++17 -Iproblem2 -c dgemv_test.cpp -o "$trial_dir/dgemv_test.o"
g++ -std=c++17 -Iproblem2 -c problem2/ref_dgemv.cpp -o "$trial_dir/ref_dgemv.o"
g++ -o "$trial_dir/x_dgemv_test" "$trial_dir/dgemv_test.o" "$trial_dir/ref_dgemv.o"

# Run
"$trial_dir/x_dgemv_test" "$trial_dir/dgemv_performance.csv"

# Check if plot script exists
if [ ! -f "scripts/plot_dgemv.py" ]; then
    echo "❌ Plotting script not found: scripts/plot_dgemv.py"
    exit 1
fi

# Plot
python3 "scripts/plot_dgemv.py" "$trial_dir/dgemv_performance.csv" "$trial_dir/dgemv_performance_plot.png"

echo "✅ Output saved to $trial_dir/"