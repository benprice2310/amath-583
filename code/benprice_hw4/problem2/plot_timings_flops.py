import pandas as pd
import matplotlib.pyplot as plt

# Load CSV data
df = pd.read_csv("results -O3/timing_results_parallel.csv")
permutations = ["ijk", "jki", "kij"]

for perm in permutations:
    plt.figure(figsize=(8, 6))
    flops = 2 * (df["size"] ** 3)
    y_float = flops / (df[f"{perm}_float"] / 1e9)
    y_double = flops / (df[f"{perm}_double"] / 1e9)

    plt.plot(df["size"], y_float, label="float", marker="o", markersize=3, linewidth=1)
    plt.plot(
        df["size"], y_double, label="double", marker="s", markersize=3, linewidth=1
    )
    plt.yscale("log")
    plt.ylim([1e6, 1e10])
    plt.xlabel("Matrix Size (x × x)")
    plt.ylabel("FLOPs / sec")
    plt.title(f"GEMM Performance - Loop Order: {perm}")
    plt.grid(True, which="both", linestyle="--", linewidth=0.5)
    plt.legend()
    plt.tight_layout()
    plt.savefig(f"gemm_flops_{perm}.png", dpi=600)

plt.show()
print("✅ Finished generating separate plots for ijk, jki, kij.")
