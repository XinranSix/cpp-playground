#include <rttr/registration>
#include <string>

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
/* void func(int) { LOG("inthefunc(int)"); }

void func() { LOG("inthefunc()"); } */

int main(int argc, char* argv[]) { return 0; }
