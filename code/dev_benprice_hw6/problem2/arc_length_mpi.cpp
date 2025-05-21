/* arc_length_mpi.cpp  –  MPI Riemann-sum arc length */

#include <mpi.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cinttypes>     // <-- adds PRIu64 macro
#include <numeric>
#include <vector>

using u64 = std::uint64_t;

inline double g(double x) noexcept { return 0.25 * x + 1.0 / x; }

int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);

    int rank, nprocs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    if (argc < 2) {
        if (rank == 0)
            std::fprintf(stderr, "Usage: %s <n_points>\n", argv[0]);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    const u64 N = std::strtoull(argv[1], nullptr, 10);

    const double a = 1.0, b = 6.0;
    const double dx = (b - a) / static_cast<double>(N);

    /* local index range (block) */
    u64 chunk = N / nprocs;
    u64 lo = rank * chunk;
    u64 hi = (rank == nprocs - 1) ? N : lo + chunk;

    double local_sum = 0.0;
    for (u64 i = lo; i < hi; ++i)
        local_sum += g(a + static_cast<double>(i) * dx);

    MPI_Barrier(MPI_COMM_WORLD);
    double t0 = MPI_Wtime();

    double global_sum = 0.0;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE,
               MPI_SUM, 0, MPI_COMM_WORLD);

    double t1 = MPI_Wtime();

    if (rank == 0) {
        const double L_num   = global_sum * dx;
        const double L_exact = 35.0 / 8.0 + std::log(6.0);
        const double err     = std::abs(L_num - L_exact);

        std::printf("n_points   = %" PRIu64 "\n", N);
        std::printf("procs      = %d\n",  nprocs);
        std::printf("time[s]    = %.15f\n", t1 - t0);
        std::printf("abs_error  = %.15e\n", err);
    }

    MPI_Finalize();
    return 0;
}
