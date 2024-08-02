#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ranges.h>

#include <map>

struct Person {
    std::string name;
    int age;
};

// 为自定义类型实现格式化函数
template <>
struct fmt::formatter<Person> {
    // 解析格式说明符
    constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
        // 在这里处理自定义格式说明符（如果需要）
        auto it = ctx.begin();
        auto end = ctx.end();
        if (it != end && *it != '}')
            throw format_error("invalid format");
        return it;
    }

    // 将自定义类型格式化为字符串
    template <typename FormatContext>
    auto format(const Person& p, FormatContext& ctx) const
        -> decltype(ctx.out()) {
        return fmt::format_to(ctx.out(), "Name: {}, Age: {}", p.name, p.age);
    }
};

int main() {

    std::map<std::string, int> m = { { "one", 1 },
                                     { "two", 2 },
                                     { "three", 3 } };

    fmt::println("{}", m);

    return 0;
}
