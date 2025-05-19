from pathlib import Path
import pandas as pd
import matplotlib.pyplot as plt

# ---------- user-adjustable ---------- #
SCALING_CSV  = Path("scaling.csv")
ERROR_CSV    = Path("error.csv")
TIME_COL     = "time_mean"
THREADS_COL  = "threads"
ERR_COL      = "abs_error"
N_COL        = "n"
OUT_TIME_PNG = Path("strong-scaling.png")
OUT_ERR_PNG  = Path("error-convergence.png")
# ------------------------------------- #

def strong_scaling(df: pd.DataFrame, fname: Path) -> None:
    """Linear–linear wall-clock time + efficiency vs. threads."""
    df = df.sort_values(THREADS_COL)
    t1 = df.loc[df[THREADS_COL] == 1, TIME_COL].iloc[0]
    eff = t1 / (df[THREADS_COL] * df[TIME_COL])

    fig, ax1 = plt.subplots()
    ax1.plot(df[THREADS_COL], df[TIME_COL], marker="o", label="time")
    ax1.set_xlabel("Thread count")
    ax1.set_ylabel("Wall-clock time [s]")
    ax1.grid(True, ls="--", alpha=0.5)

    ax2 = ax1.twinx()
    ax2.plot(df[THREADS_COL], eff,
             marker="s", ls="--", color="tab:orange", label="efficiency")
    ax2.set_ylabel("Parallel efficiency  $\\eta = T_1 /(p\\,T_p)$")
    ax2.set_ylim(0, 1.05)

    # combine legends
    h1, l1 = ax1.get_legend_handles_labels()
    h2, l2 = ax2.get_legend_handles_labels()
    ax1.legend(h1 + h2, l1 + l2, loc="best")

    fig.tight_layout()
    fig.savefig(fname, dpi=300)
    print(f"✓ saved {fname}")

def error_convergence(df: pd.DataFrame, fname: Path) -> None:
    """Log–log absolute error vs. partition points."""
    df = df.sort_values(N_COL)
    plt.figure()
    plt.loglog(df[N_COL], df[ERR_COL], marker="o")
    plt.xlabel("$n$  (partition points)")
    plt.ylabel("Absolute error")
    plt.title("Error convergence of left-Riemann sum")
    plt.grid(True, which="both", ls="--", alpha=0.5)
    plt.tight_layout()
    plt.savefig(fname, dpi=300)
    print(f"✓ saved {fname}")

def main():
    strong_scaling(pd.read_csv(SCALING_CSV), OUT_TIME_PNG)
    error_convergence(pd.read_csv(ERROR_CSV), OUT_ERR_PNG)

if __name__ == "__main__":
    main()
