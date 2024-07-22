#if defined(_MSC_VER)
    #pragma warning(push)
    #pragma warning(                                                           \
        disable : 4244) // warning C4244: 'argument': conversion from 'const T'
                        // to 'unsigned int', possible loss of data.
#endif

#include <iostream>

#include <magic_enum_containers.hpp>

enum class Color { RED = 1, GREEN = 2, BLUE = 4 };
template <>
struct magic_enum::customize::enum_range<Color> {
    static constexpr bool is_flags = true;
};

int main() {

    std::cout << std::boolalpha;
    magic_enum::containers::set color_set { Color::RED, Color::GREEN,
                                            Color::BLUE };
    std::cout << color_set.empty() << std::endl; // false
    std::cout << color_set.size() << std::endl;  // 3

    color_set.clear();
    std::cout << color_set.empty() << std::endl; // true
    std::cout << color_set.size() << std::endl;  // 0

    color_set.insert(Color::GREEN);
    color_set.insert(Color::BLUE);
    std::cout << color_set.empty() << std::endl; // false
    std::cout << color_set.size() << std::endl;  // 2

    return 0;
}
