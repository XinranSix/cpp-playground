#include <iostream>

#include "scienum.h"

enum class Color {
    RED,
    GREEN,
    BLUE,
    YELLOW,
};

/* void func(int) { LOG("inthefunc(int)"); }

void func() { LOG("inthefunc()"); } */

int main(int argc, char* argv[]) {

    std::cout << scienum::get_enum_name(Color::RED) << std::endl;

    return 0;
}
