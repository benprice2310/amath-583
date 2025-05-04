import pandas as pd
import matplotlib.pyplot as plt

# Load CSV data
df = pd.read_csv("20250504_1611_timing_results_parallel.csv")

# Set up plot
fig, axs = plt.subplots(3, 1, figsize=(12, 10), sharex=True)
permutations = ["ijk", "jki", "kij"]

for i, perm in enumerate(permutations):
    ax = axs[i]
    ax.plot(
        df["size"],
        df[f"{perm}_float"],
        label="float",
        marker="o",
        markersize=3,
        linewidth=1,
    )
    ax.plot(
        df["size"],
        df[f"{perm}_double"],
        label="double",
        marker="s",
        markersize=3,
        linewidth=1,
    )
    ax.set_yscale("log")
    ax.set_title(f"Loop Order: {perm}")
    ax.set_ylabel("Time (ns)")
    ax.grid(True, which="both", linestyle="--", linewidth=0.5)
    ax.legend()

axs[-1].set_xlabel("Matrix Size (x × x)")
fig.suptitle("GEMM Timing by Loop Permutation and Precision", fontsize=14)
plt.tight_layout()
plt.savefig("gemm_parallel_timing_subplot.png", dpi=600)
plt.show()
