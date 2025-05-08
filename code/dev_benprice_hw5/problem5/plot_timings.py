import numpy as np
import matplotlib.pyplot as plt

# --- Load data ---
# CSV columns: n, avg_time_ms, gflops
data = np.loadtxt("strassen_perf.csv", delimiter=",", skiprows=1)
n = data[:, 0]
time_ms = data[:, 1]
gflops = data[:, 2]

# --- Plot ---
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(6, 8))

# 1) Time vs n
ax1.loglog(n, time_ms, "o-")  # no basex/basey here
ax1.set_xscale("log", base=2)  # x‐axis in base-2
ax1.set_yscale("log", base=10)  # y‐axis in base-10
ax1.set_xlabel("Matrix size n")
ax1.set_ylabel("Avg time (ms)")
ax1.set_title("Strassen Multiply: Time vs n")
ax1.grid(True, which="both", ls="--", alpha=0.5)

# 2) GFLOP/s vs n
ax2.loglog(n, gflops, "s-")  # no basex/basey
ax2.set_xscale("log", base=2)
ax2.set_yscale("log", base=10)
ax2.set_xlabel("Matrix size n")
ax2.set_ylabel("Effective GFLOP/s")
ax2.set_title("Strassen Multiply: Efficiency vs n")
ax2.grid(True, which="both", ls="--", alpha=0.5)

plt.tight_layout()

# --- Save to high-dpi PNG ---
plt.savefig("strassen_performance.png", dpi=300)

# --- Show on screen ---
plt.show()
