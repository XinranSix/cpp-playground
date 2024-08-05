#include <iostream>
#include <memory>

const int& f() {
    int i {};
    return i;
}

int main(int argc, char* argv[]) {
    // std::cout << "Hello World" << std::endl;

    f();

    return 0;
}
