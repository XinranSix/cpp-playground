// 04_thread_self_manage.cpp

#include <iomanip>
#include <print>
#include <sstream>
#include <thread>

void print_time() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(localtime(&in_time_t), "%Y-%m-%d %X");
    std::println("now is: {}", ss.str());
}

void sleep_thread() {

    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::println("[thread-{}] is waking up", std::this_thread::get_id());
}

void loop_thread() {
    for (int i = 0; i < 10; i++) {
        std::println("[thread-{}] print: {}", std::this_thread::get_id(), i);
    }
}

int main() {
    print_time();

    std::thread t1(sleep_thread);
    std::thread t2(loop_thread);

    t1.join();
    t2.detach();

    print_time();
    return 0;
}
