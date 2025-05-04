import pandas as pd
import matplotlib.pyplot as plt

# Read timing results
df = pd.read_csv("timing_results.csv")

# Setup plot
fig, axs = plt.subplots(3, 1, figsize=(10, 8), sharex=True)

# Row 1: ijk
axs[0].plot(df["size"], df["ijk_float"], marker="o", label="float")
axs[0].plot(df["size"], df["ijk_double"], marker="s", label="double")
axs[0].set_ylabel("Time (ns)")
axs[0].set_yscale("log")
axs[0].set_title("Loop Order: ijk")
axs[0].legend()
axs[0].grid(True)

# Row 2: jki
axs[1].plot(df["size"], df["jki_float"], marker="o", label="float")
axs[1].plot(df["size"], df["jki_double"], marker="s", label="double")
axs[1].set_ylabel("Time (ns)")
axs[1].set_yscale("log")
axs[1].set_title("Loop Order: jki")
axs[1].legend()
axs[1].grid(True)

# Row 3: kij
axs[2].plot(df["size"], df["kij_float"], marker="o", label="float")
axs[2].plot(df["size"], df["kij_double"], marker="s", label="double")
axs[2].set_xlabel("Matrix Size (x × x)")
axs[2].set_ylabel("Time (ns)")
axs[2].set_yscale("log")
axs[2].set_title("Loop Order: kij")
axs[2].legend()
axs[2].grid(True)

# Final formatting
plt.suptitle("GEMM Timing by Loop Permutation and Precision", fontsize=14)
plt.tight_layout()
# plt.subplots_adjust(top=0.92)
plt.savefig("gemm_timings_subplot.png")
plt.show()
