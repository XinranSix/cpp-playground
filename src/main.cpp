#include <coroutine>
#include <iostream>
#include <optional>

// 定义一个简单的协程返回类型
struct FibonacciGenerator {
    struct promise_type {
        std::optional<int> current_value;

        FibonacciGenerator get_return_object() {
            return FibonacciGenerator {
                std::coroutine_handle<promise_type>::from_promise(*this)
            };
        }

        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() { std::terminate(); }

        std::suspend_always yield_value(int value) {
            current_value = value;
            return {};
        }

        void return_void() {}
    };

    std::coroutine_handle<promise_type> handle;

    bool move_next() {
        if (handle) {
            handle.resume();
            return !handle.done();
        }
        return false;
    }

    int current_value() {
        if (handle && handle.promise().current_value) {
            return *handle.promise().current_value;
        }
        return -1; // 默认值，表示没有值
    }

    ~FibonacciGenerator() {
        if (handle)
            handle.destroy();
    }
};

// 生成斐波那契数列的协程函数
FibonacciGenerator fibonacci() {
    int a = 0, b = 1;
    while (true) {
        co_yield b;
        int next = a + b;
        a = b;
        b = next;
    }
}

int main() {
    auto gen = fibonacci();
    for (int i = 0; i < 10; ++i) {
        gen.move_next();
        std::cout << gen.current_value() << " ";
    }
    std::cout << std::endl;
    return 0;
}
