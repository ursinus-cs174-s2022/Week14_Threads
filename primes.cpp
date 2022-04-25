#include <thread>
#include <chrono>
#include <mutex>
#include <iostream>
#include <functional>
#include <time.h>
#include <stdio.h>

#define NUM_THREADS 12

using namespace std;

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::milliseconds milliseconds;

void printPrime(int x) {
    bool isPrime = true;
    int i = 2;
    while (i < x && isPrime) {
        if (x%i == 0) {
            isPrime = false;
        }
        i++;
    }
    if (isPrime) {
        cout << x << " ";
    }
}


int main(int argc, char** argv) {
    thread* threads[NUM_THREADS];
    Clock::time_point tic = Clock::now();
    
    int N = atoi(argv[1]);
    for (int x = 2; x < N; x++) {
        printPrime(x);
    }

    Clock::time_point toc = Clock::now();
    milliseconds ms = std::chrono::duration_cast<milliseconds>(toc-tic);
    cout << "\n\nTime elapsed: " << ms.count()  << "ms\n";
}
