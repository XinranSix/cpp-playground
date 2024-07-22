#include <gsl/pointers>

#include <iostream>
#include <memory>
#include <type_traits>

void test() {
    gsl::owner<int*> p;
    /* gsl::owner<int&>;                   // Error
    gsl::owner<int> w;                  // Error
    gsl::owner<std::unique_ptr<int>> u; // Error
    gsl::owner<std::shared_ptr<int>> s; // Error */
}

int main(int argc, char* argv[]) {

    using type = std::add_const_t<const int>;
    static_assert(std::is_same_v<type, const int>, "");

    return 0;
}
