// 06_naive_multithread.cpp

#include <chrono>
#include <cmath>
#include <print>
#include <thread>
#include <vector>

static const int MAX = 10e8; // ①
static double sum = 0;       // ②

void worker(int min, int max) { // ③
    for (int i = min; i <= max; i++) {
        sum += sqrt(i);
    }
}

void serial_task(int min, int max) { // ④
    auto start_time = std::chrono::steady_clock::now();
    sum = 0;
    worker(0, MAX);
    auto end_time = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time -
                                                                    start_time)
                  .count();
    std::println("Serail task finish, {} ms consumed, Result: {}", ms, sum);
}

void concurrent_task(int min, int max) {
    auto start_time = std::chrono::steady_clock::now();

    unsigned concurrent_count = std::thread::hardware_concurrency(); // ①
    std::println("hardware_concurrency: {}", concurrent_count);
    std::vector<std::thread> threads;
    min = 0;
    sum = 0;
    for (int t = 0; t < concurrent_count; t++) { // ②
        int range = max / concurrent_count * (t + 1);
        threads.push_back(std::thread(worker, min, range)); // ③
        min = range + 1;
    }
    for (auto& t : threads) {
        t.join(); // ④
    }

    auto end_time = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time -
                                                                    start_time)
                  .count();
    std::println("Concurrent task finish, {} ms consumed, Result: {}", ms, sum);
}

int main(int argc, char* argv[]) {
    serial_task(0, MAX);
    concurrent_task(0, MAX);
    return 0;
}
