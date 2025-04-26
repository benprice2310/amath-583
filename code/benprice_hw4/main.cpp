#include <iostream>
#include <vector>
#include <chrono>

int main()
{
    int i = 1;
    long double elapsed_time = 0.L;

    std::cout << "\ni: " << i++ << '\n'; // use then increment. print 1, set i = 2.
    std::cout << "\ni: " << ++i << '\n'; // increment then use. set i = 3, print 3.

    std::cout << "\n=== For loop, i++ ===\n\n";
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 5; i++)
    {
        std::cout << "i: " << i << '\n';
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    elapsed_time += duration.count() * 1.e-9;
    std::cout << "elapsed time: " << elapsed_time * 1e9 << " ns\n";
    elapsed_time = 0.L;

    std::cout << "\n=== For loop, ++j ===\n\n";
    start = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < 5; ++j)
    {
        std::cout << "j: " << j << '\n';
    }
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    elapsed_time += duration.count() * 1.e-9;
    std::cout << "elapsed time: " << elapsed_time * 1e9 << " ns\n";
    elapsed_time = 0.L;

    std::cout << "\n=== Vectors ===\n";
    std::vector<int> vec{1, 2, 3, 4, 5};

    // BAD style (small inefficiency)
    start = std::chrono::high_resolution_clock::now();
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
    {
        std::cout << *it << " ";
    }
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    elapsed_time += duration.count() * 1.e-9;
    std::cout << "elapsed time: " << elapsed_time * 1e9 << " ns\n";
    elapsed_time = 0.L;
    std::cout << '\n'
              << '\n';

    // BETTER style (no unnecessary copy)
    start = std::chrono::high_resolution_clock::now();
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        std::cout << *it << " ";
    }
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    elapsed_time += duration.count() * 1.e-9;
    std::cout << "elapsed time: " << elapsed_time * 1e9 << " ns\n";
    elapsed_time = 0.L;
    std::cout << '\n';
}