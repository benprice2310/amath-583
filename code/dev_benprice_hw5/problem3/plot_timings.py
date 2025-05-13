import numpy as np
import matplotlib.pyplot as plt

# load the CSV generated above
data = np.loadtxt("timings.csv", delimiter=",", skiprows=1)
N = data[:, 0]
t_row = data[:, 1]
t_col = data[:, 2]

plt.figure(figsize=(6, 4))
plt.loglog(N, t_row, "o-", label="row swap")
plt.loglog(N, t_col, "s-", label="col swap")
plt.xlabel("Matrix size N")
plt.ylabel("Avg swap time (μs)")
plt.title("Row vs Column Swap Timing (log–log)")
plt.legend()
plt.grid(True, which="both", ls="--", alpha=0.5)
plt.tight_layout()

# export to high-dpi PNG
plt.savefig("row_col_swap_timing.png", dpi=300)

plt.show()
