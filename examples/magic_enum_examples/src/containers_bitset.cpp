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

    auto color_bitset = magic_enum::containers::bitset<Color>();
    color_bitset.set(Color::GREEN);
    color_bitset.set(Color::BLUE);

    std::cout << std::boolalpha;
    std::cout << color_bitset.size()
              << std::endl; // 3 == magic_enum::enum_count<Color>()
    std::cout << color_bitset.all() << std::endl;              // false
    std::cout << color_bitset.any() << std::endl;              // true
    std::cout << color_bitset.none() << std::endl;             // false
    std::cout << color_bitset.count() << std::endl;            // 2
    std::cout << color_bitset.test(Color::RED) << std::endl;   // false
    std::cout << color_bitset.test(Color::GREEN) << std::endl; // true
    std::cout << color_bitset.test(Color::BLUE) << std::endl;  // true

    return 0;
}
