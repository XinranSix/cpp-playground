#include <print>
#include <thread>

void hello() { std::println("Hello World from new thread."); }

int main() {
    std::thread t(hello);
    t.join();

    return 0;
}
