#include "range/v3/view/for_each.hpp"
#include <fmt/ranges.h>
#include <iostream>
#include <range/v3/all.hpp> // get everything
#include <string>

int main() {

    std::vector<int> vi { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    using namespace ranges;
    auto rng = vi | views::remove_if([](int i) { return i % 2 == 1; }) |
               views::transform([](int i) { return std::to_string(i); });
    // rng == {"2","4","6","8","10"};

    fmt::println("{}", vi);

    return 0;
}
