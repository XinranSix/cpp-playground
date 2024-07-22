#include <iostream>
#include <print>
// #include <string>

#include <rttr/registration>

using namespace rttr;

struct MyStruct {
    MyStruct() {};
    void func(double) {};
    int data;
};

RTTR_REGISTRATION {
    registration::class_<MyStruct>("MyStruct")
        .constructor<>()
        .property("data", &MyStruct::data)
        .method("func", &MyStruct::func);
}

int main(int argc, char* argv[]) {

    type t = type::get<MyStruct>();
    for (auto& prop : t.get_properties()) {
        std::cout << "name: " << prop.get_name() << std::endl;
    }

    for (auto& meth : t.get_methods()) {
        std::cout << "name: " << meth.get_name() << std::endl;
    }

    return 0;
}
