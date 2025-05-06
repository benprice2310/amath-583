# plot_problem6.py

import pandas as pd
import matplotlib.pyplot as plt

# Load timing data
df = pd.read_csv("output/swap_timings.csv")

# Plot
plt.figure(figsize=(8, 6))
plt.plot(df["size"], df["row_swap_time"], marker="o", label="Row Swap")
plt.plot(df["size"], df["col_swap_time"], marker="s", label="Column Swap")

plt.xlabel("Matrix Dimension (N)")
plt.ylabel("Average Time [s]")
plt.title("File Swap Performance vs Matrix Size")
plt.legend()
plt.grid(True)
plt.yscale("log")
# plt.xticks(df["size"], rotation=45)
plt.tight_layout()
plt.savefig("output/problem6_swap_plot.png", dpi=600)
plt.show()
