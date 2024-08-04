#include <fmt/ranges.h>
#include <iostream>
#include <string>
#include <vector>

int main() {

    std::vector<uint8_t> s = {
        0xE6, 0x88, 0x91,       // 我，需要三级列车
        0xE7, 0x88, 0xB1,       // 爱，需要三级列车
        0xF0, 0xB0, 0xAF, 0x9B, // 𰻞，需要四级列车
        0xF0, 0xB0, 0xAF, 0x9B, // 𰻞，需要四级列车
        0xE9, 0x9D, 0xA2,       // 面，需要三级列车
        0x21, // !，这是个 ASCII 范围的字符，直接用单个火车头装
    };

    return 0;
}
