// 03_thread_argument.cpp

#include <print>
#include <string>
#include <thread>

void hello(std::string name) { std::println("Welcome to: {}", name); }

int main() {
    // std::thread t(hello, "https://paul.pub");
    std::thread t(hello, "https://paul.pub");
    t.join();

    return 0;
}
