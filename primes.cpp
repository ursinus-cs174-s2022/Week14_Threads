#include <thread>
#include <chrono>
#include <mutex>
#include <iostream>
#include <functional>
#include <time.h>
#include <stdio.h>

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
void loopPrimes(int x, int chunkSize){
    for(int i = x; i < x + chunkSize; i++){
        printPrime(i);
    }
}

int main(int argc, char** argv) {
    int numThreads = atoi(argv[1]);
    thread* threads[numThreads];
    int chunkSize = atoi(argv[2]) / numThreads;
    Clock::time_point tic = Clock::now();
    
    int N = atoi(argv[1]);
    for (int i = 0; i < numThreads; i++) {
        threads[i] = new thread(loopPrimes, i * chunkSize, chunkSize);
    }
    for (int i = 0; i < numThreads; i++) {
        threads[i]->join();
    }
    Clock::time_point toc = Clock::now();
    milliseconds ms = std::chrono::duration_cast<milliseconds>(toc-tic);
    cout << "\n\nTime elapsed: " << ms.count()  << "ms\n";
    /*
    for(int i = 0; i < numThreads; i++){
        delete threads[i];
    }
    delete[] threads;
    */
}
