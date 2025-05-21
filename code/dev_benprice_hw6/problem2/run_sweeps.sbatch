#!/bin/bash
#SBATCH -J arc-sweeps
#SBATCH -A <your_account>
#SBATCH -p <your_partition>
#SBATCH -N 2               # enough nodes for up to 32 ranks
#SBATCH -t 00:20:00
#SBATCH -o sweeps.out
#SBATCH -e sweeps.err
#SBATCH --exclusive        # optional – full nodes

module load gcc openmpi    # same toolchain used at compile time
export OMP_NUM_THREADS=1   # ensure pure MPI

############  parameters  ############
N_POINTS_SCALE=100000000        # 1e8
PART_LIST=(1 2 4 8 16 32)       # strong-scaling ranks
N_LIST=(10 100 1000 10000 100000 1000000)
######################################

echo "▶ strong scaling sweep"   >  scaling.csv
echo "threads,time_mean"        >> scaling.csv
for p in "${PART_LIST[@]}"; do
    t=$(srun -n "$p" --mpi=pmix ./arc_length_mpi $N_POINTS_SCALE \
        | awk -F'=' '/time/{print $2}')
    echo "$p,$t" >> scaling.csv
    echo "  p=$p  t=$t"
done

echo "▶ error sweep"
echo "n,abs_error" > error.csv
for n in "${N_LIST[@]}"; do
    err=$(srun -n 1 --mpi=pmix ./arc_length_mpi "$n" \
        | awk -F'=' '/abs_error/{print $2}')
    echo "$n,$err" >> error.csv
    echo "  n=$n  err=$err"
done
