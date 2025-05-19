#include <algorithm>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

using u64 = std::uint64_t;

inline double g(double x) noexcept {          // simplified integrand
    return x * 0.25 + 1.0 / x;                //  x/4 + 1/x
}

double integrate(u64 n, int nthreads) {
    const double a  = 1.0, b = 6.0;
    const double dx = (b - a) / static_cast<double>(n);

    std::vector<double> partial(nthreads, 0.0);

    auto worker = [&](int tid) {
        u64 i0 = tid * (n / nthreads);
        u64 i1 = (tid == nthreads - 1) ? n : (tid + 1) * (n / nthreads);

        double local = 0.0;
        for (u64 i = i0; i < i1; ++i) {
            double x = a + static_cast<double>(i) * dx;   // left node
            local += g(x);
        }
        partial[tid] = local;
    };

    std::vector<std::thread> pool;
    for (int t = 0; t < nthreads; ++t) pool.emplace_back(worker, t);
    for (auto& th : pool) th.join();

    return std::accumulate(partial.begin(), partial.end(), 0.0) * dx;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <n_points> <n_threads> [trials]\n";
        return 1;
    }
    const u64   n_points = std::stoull(argv[1]);
    const int   nthreads = std::stoi(argv[2]);
    const int   trials   = (argc > 3) ? std::stoi(argv[3]) : 1;

    const double L_exact = 35.0 / 8.0 + std::log(6.0);

    std::vector<double> times, errs;
    times.reserve(trials);
    errs .reserve(trials);

    for (int k = 0; k < trials; ++k) {
        auto t0 = std::chrono::steady_clock::now();
        double L_num = integrate(n_points, nthreads);
        auto t1 = std::chrono::steady_clock::now();

        times.push_back(std::chrono::duration<double>(t1 - t0).count());
        errs .push_back(std::fabs(L_num - L_exact));
    }

    auto mean = [](const std::vector<double>& v) {
        return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
    };

    std::cout << std::setprecision(15)
              << "n_points    = " << n_points               << '\n'
              << "threads     = " << nthreads               << '\n'
              << "trials      = " << trials                 << '\n'
              << "time_mean   = " << mean(times)            << '\n'
              << "time_min    = " << *std::min_element(times.begin(), times.end()) << '\n'
              << "abs_error   = " << mean(errs)             << '\n';
}
// --------------------------------------------------------------
// End of arc_length.cpp
// --------------------------------------------------------------