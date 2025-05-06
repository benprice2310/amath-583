# plot_bandwidth.py
import pandas as pd
import matplotlib.pyplot as plt

# Load timing data
df = pd.read_csv("output/io_bandwidth.csv")  # Adjust path if needed

# Plotting
plt.figure(figsize=(10, 6))
plt.plot(df["N"], df["write_bandwidth_Bps"], marker="o", label="Write Bandwidth")
plt.plot(df["N"], df["read_bandwidth_Bps"], marker="s", label="Read Bandwidth")

# Axis labels and formatting
plt.xlabel("Matrix Dimension N")
plt.ylabel("Bandwidth (Bytes/s)")
plt.title("Read and Write Bandwidth vs. Matrix Size (N)")
plt.legend()
plt.grid(True)
plt.yscale("log")
plt.tight_layout()

# Show and save
plt.savefig("output/problem5_bandwidth_plot.png", dpi=600)
plt.show()
