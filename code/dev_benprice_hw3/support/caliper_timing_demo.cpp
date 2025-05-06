#include <iostream>

void printSeperator(const std::string &msg)
{
    std::cout << "\n=== " << msg << " ===\n\n";
}

int main()
{
    printSeperator("Welcome to Amath 583 assignment 3 by Ben Price");

    // timer foo
    auto start = std::chrono::high_resolution_clock::now();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    long double elapsed_time = 0.L;
    long double avg_time;
    const int ntrials = 3;

    // loop on problem size
    for (int i = 2; i <= 128; i++)
    {
        // perform an experiment
        for (int t = 0; t < ntrials; t++)
        {
            start = std::chrono::high_resolution_clock::now();
            // do work(size i, trial t)
            stop = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
            elapsed_time += (duration.count() * 1.e-9); // Convert to seconds
        }
        avg_time = elapsed_time / static_cast<long double>(ntrials);
        // save or report findings

        std::cout << "size " << i << "\n";
        std::cout << "Final elapsed time: " << elapsed_time << " s\n";
        std::cout << "Average time: " << avg_time << " s\n\n";

        // zero time again
        elapsed_time = 0.L;
    }

    return 0;
}