#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/os.h>
#include <fmt/ranges.h>
#include <print>
#include <vector>

auto main(int argc, char *argv[]) -> int {

    {
        fmt::println("hello, world");
        std::string s1 = fmt::format("The answer is {}.", 42);
        fmt::println("{}", s1);
        std::string s2 =
            fmt::format("I'd rather be {1} than {0}.", "right", "happy");
        fmt::println("{}", s2);
    }

    {
        auto now = std::chrono::system_clock::now();
        fmt::println("Date and time: {}", now);
        fmt::println("Time: {:%H:%M}", now);
    }

    {
        std::vector<int> v = { 1, 2, 3 };
        fmt::println("{}", v);
    }

    {
        auto out = fmt::output_file("guide.txt");
        out.print("Don't {}", "Panic");
    }

    {
        fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold,
                   "Hello, {}!\n", "world");
        fmt::print(fg(fmt::color::floral_white) | bg(fmt::color::slate_gray) |
                       fmt::emphasis::underline,
                   "Olá, {}!\n", "Mundo");
        fmt::print(fg(fmt::color::steel_blue) | fmt::emphasis::italic,
                   "你好{}！\n", "世界");
    }

    {
        std::time_t t = std::time(nullptr);

        fmt::print("The date is {:%Y-%m-%d}.", fmt::localtime(t));
        // Output: The date is 2020-11-07.
        // (with 2020-11-07 replaced by the current date)

        using namespace std::literals::chrono_literals;

        fmt::print("Default format: {} {}\n", 42s, 100ms);
        // Output: Default format: 42s 100ms

        fmt::print("strftime-like format: {:%H:%M:%S}\n", 3h + 15min + 30s);
        // Output: strftime-like format: 03:15:30
    }

    {
        std::print("std::print\n");
        std::println("std::println");
        std::println("{}", 1);
    }

    return 0;
}
