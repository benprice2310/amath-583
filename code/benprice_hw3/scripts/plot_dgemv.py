import sys
import pandas as pd
import matplotlib.pyplot as plt
import os

# CLI args
csv_path = sys.argv[1]
png_path = sys.argv[2]

# Check if the CSV file exists
if not os.path.exists(csv_path):
    print(f"Error: The file {csv_path} does not exist.")
    sys.exit(1)

data = pd.read_csv(csv_path)

plt.figure(figsize=(8, 6))
plt.plot(data['n'], data['FLOPs_per_sec'] / 1e6, marker='o', markersize=3)
plt.xlabel("Vector Size n")
plt.ylabel("MFLOPs/sec")
plt.title("DGEMV Performance")
# plt.grid(True)
plt.fontsize = 24
plt.xscale('log')
plt.tight_layout()
plt.savefig(png_path, dpi=300)
plt.show()