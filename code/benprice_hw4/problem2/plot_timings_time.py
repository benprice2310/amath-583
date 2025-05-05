import pandas as pd
import matplotlib.pyplot as plt

# Load CSV data
df = pd.read_csv("timing_results_parallel.csv")
permutations = ["ijk", "jki", "kij"]

for perm in permutations:
    plt.figure(figsize=(10, 6))
    plt.plot(
        df["size"],
        df[f"{perm}_float"],
        label="float",
        marker="o",
        markersize=3,
        linewidth=1,
    )
    plt.plot(
        df["size"],
        df[f"{perm}_double"],
        label="double",
        marker="s",
        markersize=3,
        linewidth=1,
    )
    plt.yscale("log")
    plt.xlabel("Matrix Size (x × x)")
    plt.ylabel("Time (ns)")
    plt.title(f"GEMM Timing - Loop Order: {perm}")
    plt.grid(True, which="both", linestyle="--", linewidth=0.5)
    plt.ylim((1e0, 1e10))
    plt.legend()
    plt.tight_layout()
    plt.savefig(f"gemm_timing_{perm}.png", dpi=600)
    # plt.close()

plt.show()
print("✅ Finished generating separate plots for ijk, jki, kij.")
