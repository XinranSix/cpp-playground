// 02_lambda_thread.cpp

#include <print>
#include <thread>

int main() {
    std::thread t([] { std::println("Hello World from lambda thread."); });

    t.join();

    return 0;
}
