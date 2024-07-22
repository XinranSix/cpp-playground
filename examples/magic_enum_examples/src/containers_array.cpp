#include <iostream>

#include <magic_enum_containers.hpp>

enum class Color { RED = 1, GREEN = 2, BLUE = 4 };
template <>
struct magic_enum::customize::enum_range<Color> {
    static constexpr bool is_flags = true;
};

struct RGB {

    std::uint8_t r {};
    std::uint8_t g {};
    std::uint8_t b {};

    [[nodiscard]] constexpr bool empty() {
        return std::equal_to {}(r, g) && std::equal_to {}(g, b) &&
               std::equal_to {}(b, 0);
    }

    [[nodiscard]] constexpr bool operator==(RGB rgb) const noexcept {
        return std::equal_to {}(r, rgb.r) && std::equal_to {}(g, rgb.g) &&
               std::equal_to {}(b, rgb.b);
    }

    friend std::ostream& operator<<(std::ostream& ostream, RGB rgb) {
        ostream << "R=" << static_cast<std::uint32_t>(rgb.r)
                << " G=" << static_cast<std::uint32_t>(rgb.g)
                << " B=" << static_cast<std::uint32_t>(rgb.b);
        return ostream;
    }
};

constexpr std::uint8_t color_max = std::numeric_limits<std::uint8_t>::max();

int main() {

    constexpr magic_enum::containers::array<Color, RGB> color_rgb_initializer {
        { { { color_max, 0, 0 }, { 0, color_max, 0 }, { 0, 0, color_max } } }
    };

    std::cout << magic_enum::containers::get<0>(color_rgb_initializer)
              << std::endl; // R=255 G=0 B=0
    std::cout << magic_enum::containers::get<1>(color_rgb_initializer)
              << std::endl; // R=0 G=255 B=0
    std::cout << magic_enum::containers::get<2>(color_rgb_initializer)
              << std::endl; // R=0 G=0 B=255

    std::cout << magic_enum::containers::get<Color::RED>(color_rgb_initializer)
              << std::endl; // R=255 G=0 B=0
    std::cout << magic_enum::containers::get<Color::GREEN>(
                     color_rgb_initializer)
              << std::endl; // R=0 G=255 B=0
    std::cout << magic_enum::containers::get<Color::BLUE>(color_rgb_initializer)
              << std::endl; // R=0 G=0 B=255

    return 0;
}
