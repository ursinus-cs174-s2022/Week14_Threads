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

class Counter {
    public:
        int x;
        Counter(){
            x = 0;
        }
        void addOne() {
            x++;
        }
        void subtractOne() {
            x--;
        }
};

void func(Counter* c, int numThreads, mutex& m) {
    for (int i = 0; i < 100000000/numThreads; i++) {
        m.lock();
        c->addOne();
        m.unlock();
        
        m.lock();
        c->subtractOne();
        m.unlock();
    }
}

int main(int argc, char** argv) {
    Counter c;
    mutex m;
    int numThreads = atoi(argv[1]);
    thread* threads[numThreads];
    Clock::time_point tic = Clock::now();
    for (int i = 0; i < numThreads; i++) {
        threads[i] = new thread(func, &c, numThreads, ref(m));
    }
    for (int i = 0; i < numThreads; i++) {
        threads[i]->join();
    }
    cout << c.x << "\n";
    for (int i = 0; i < numThreads; i++) {
        delete threads[i];
    }
    Clock::time_point toc = Clock::now();
    milliseconds ms = std::chrono::duration_cast<milliseconds>(toc-tic);
    cout << "Time elapsed: " << ms.count()  << "ms\n";
}
