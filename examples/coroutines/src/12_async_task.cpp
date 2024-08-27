// 12_async_task.cpp

#include <future>
#include <print>

static const int MAX = 10e8;
static double sum = 0;

void worker(int min, int max) {
    for (int i = min; i <= max; i++) {
        sum += sqrt(i);
    }
}

int main() {
    sum = 0;
    auto f1 = std::async(worker, 0, MAX);
    std::println("Async task triggered");
    f1.wait();
    std::println("Async task finish, result: {}\n", sum);
}
