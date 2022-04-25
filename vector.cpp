#include <thread>
#include <mutex>
#include <iostream>
#include <vector>
using namespace std;


#define NUM_THREADS 100

void push_back(vector<int>& v, int i) {
    v.push_back(i);
}

int main() {
    thread* threads[NUM_THREADS];
    vector<int> v;
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i] = new thread(push_back, ref(v), i);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i]->join();
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        delete threads[i];
    }
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i] << ", ";
    }
    cout << "\n";
    return 0;
}
