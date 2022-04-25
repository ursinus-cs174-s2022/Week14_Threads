#include <thread>
#include <chrono>
#include <mutex>
#include <iostream>
#include <functional>
#include <time.h>
#include <stdio.h>
using namespace std;

void printNum(int i, int chunkSize) {
    for (int k = i; k < i+chunkSize; k++) {
        cout << k << "\n";
    }
}

int main(int argc, char** argv) {
    int nthreads = atoi(argv[1]);
    thread** threads = new thread*[nthreads];
    int maxNum = 1000;
    int chunkSize = maxNum / nthreads;
    for (int i = 0; i < nthreads; i++) {
        threads[i] = new thread(printNum, i*chunkSize, chunkSize);
    }
    cout << "Finished constructing threads\n";
    for (int i = 0; i < nthreads; i++) {
        threads[i]->join(); // Wait until thread is done
    }
    for (int i = 0; i < nthreads; i++) {
        delete threads[i];
    }
    delete [] threads;
}