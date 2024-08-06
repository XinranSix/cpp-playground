// 13_packaged_task.cpp

#include <chrono>
#include <future>
#include <iostream>
#include <thread>

static const int MAX = 10e8;

double concurrent_worker(int min, int max) {
    double sum = 0;
    for (int i = min; i <= max; i++) {
        sum += sqrt(i);
    }
    return sum;
}

double concurrent_task(int min, int max) {
    std::vector<std::future<double>> results; // ①

    unsigned concurrent_count = std::thread::hardware_concurrency();
    min = 0;
    for (int i = 0; i < concurrent_count; i++) {                      // ②
        std::packaged_task<double(int, int)> task(concurrent_worker); // ③
        results.push_back(task.get_future());                         // ④

        int range = max / concurrent_count * (i + 1);
        std::thread t(std::move(task), min, range); // ⑤
        t.detach();

        min = range + 1;
    }

    std::cout << "threads create finish" << std::endl;
    double sum = 0;
    for (auto& r : results) {
        sum += r.get(); // ⑥
    }
    return sum;
}

int main() {
    auto start_time = std::chrono::steady_clock::now();

    double r = concurrent_task(0, MAX);

    auto end_time = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time -
                                                                    start_time)
                  .count();
    std::cout << "Concurrent task finish, " << ms
              << " ms consumed, Result: " << r << std::endl;
    return 0;
}
