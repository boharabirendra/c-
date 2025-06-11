#include <cmath>
#include <vector>
#include <chrono>
#include <thread>
#include <atomic>
#include <iostream>

std::atomic_int totalPrimeNumbers = 0;
int MAX_INT = 100000000;
int CONCURRENCY = 10;
std::atomic_int currentNumber = 2;

void checkPrime(int i)
{
    for (int j = 2; j <= static_cast<int>(std::sqrt(i)); j++)
    {
        if (i % j == 0)
        {
            return;
        }
    }
    totalPrimeNumbers++;
}

void doWork(int tNum)
{
    auto start = std::chrono::high_resolution_clock::now();

    for (;;)
    {

        int x = ++currentNumber;

        if (x > MAX_INT)
        {
            break;
        }

        checkPrime(x);
    }

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);

    std::cout << "Thread: " << tNum << " completed in: " << duration.count() << " seconds" << std::endl;
}

int main()
{

    int batchSize = MAX_INT / CONCURRENCY;

    std::vector<std::thread> threads;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 1; i <= CONCURRENCY; i++)
    {
        threads.emplace_back(doWork, i);
    }

    for (auto &thread : threads)
    {
        thread.join();
    }

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);

    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
    std::cout << "Total prime numbers: " << (totalPrimeNumbers + 1) << std::endl;

    return 0;
}
