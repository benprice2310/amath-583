import subprocess
import shlex
import statistics
import csv
from pathlib import Path

# ------------------------------------------------------------------- #
#  USER SETTINGS – tweak to taste
# ------------------------------------------------------------------- #
BIN            = Path(__file__).resolve().parent / "arc_length"      # compiled C++ executable
# BIN            = Path("arc_length")        # compiled C++ executable 
N_POINTS_SCALE = int(1e8)                  # mesh size for strong scaling
THREADS_LIST   = [1, 2, 4, 8, 16]          # thread counts to test
N_LIST_ERROR   = [10**k for k in range(1, 7)]  # 10, 100, ... 1e6
N_TRIALS       = 50                         # repeats per measurement
USE_TRIAL_ARG  = True                      # executable supports [trials] arg?
# ------------------------------------------------------------------- #

def run_one(cmd: str) -> str:
    """Execute *cmd* and return stdout (stderr merged)."""
    try:
        out = subprocess.check_output(shlex.split(cmd), text=True, stderr=subprocess.STDOUT)
        return out.strip()
    except subprocess.CalledProcessError as e:
        print(e.output)
        raise

def parse_time(out: str) -> float:
    """Extract *time_mean* (preferred) or *elapsed* value from program output."""
    for line in out.splitlines():
        if line.startswith("time_mean"):
            return float(line.split("=")[1])
        if line.startswith("elapsed"):
            return float(line.split("=")[1])
    raise RuntimeError("Timing line not found; check program output format.")

def parse_error(out: str) -> float:
    """Extract *abs_error* value from program output."""
    for line in out.splitlines():
        if line.startswith("abs_error"):
            return float(line.split("=")[1])
    raise RuntimeError("abs_error line not found; check program output format.")

# ====================  STRONG SCALING  ==================== #
print("▶ strong scaling sweep")
with open("scaling.csv", "w", newline="") as fcsv:
    wr = csv.writer(fcsv)
    wr.writerow(["threads", "time_mean"])
    for p in THREADS_LIST:
        times = []
        cmd_common = f"{BIN} {N_POINTS_SCALE} {p}"
        if USE_TRIAL_ARG:
            # let the executable loop internally
            out = run_one(f"{cmd_common} {N_TRIALS}")
            times.append(parse_time(out))          # already averaged
        else:
            # loop manually
            for _ in range(N_TRIALS):
                out = run_one(cmd_common)
                times.append(parse_time(out))
        t_mean = statistics.mean(times)
        wr.writerow([p, t_mean])
        print(f"  p={p:>2}  mean={t_mean:8.4f} s   {times}")

print("✓ wrote scaling.csv")

# ====================  ERROR SWEEP  ==================== #
print("▶ error-vs-n sweep")
with open("error.csv", "w", newline="") as fcsv:
    wr = csv.writer(fcsv)
    wr.writerow(["n", "abs_error"])
    for n in N_LIST_ERROR:
        errs = []
        cmd_common = f"{BIN} {n} 1"            # single thread for accuracy study
        if USE_TRIAL_ARG:
            out = run_one(f"{cmd_common} {N_TRIALS}")
            errs.append(parse_error(out))      # averaged by executable
        else:
            for _ in range(N_TRIALS):
                out = run_one(cmd_common)
                errs.append(parse_error(out))
        err_mean = statistics.mean(errs)
        wr.writerow([n, err_mean])
        print(f"  n={n:<7}  err={err_mean:.3e}")

print("✓ wrote error.csv")
