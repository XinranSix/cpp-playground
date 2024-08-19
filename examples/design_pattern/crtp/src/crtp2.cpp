#include <print>

struct Ts {
    int a {};

    void f(this Ts& self) { self.a = 100; }

    void f(this const Ts& self) {}
};

struct Base {
    void name(this auto&& self) { self.impl(); }
};

struct D1 : Base {
    friend Base;

private:
    void impl() { std::println("D1::impl()"); }
};

struct D2 : Base {
    friend Base;

private:
    void impl() { std::println("D2::impl()"); }
};

int main(int argc, char* argv[]) {

    Ts ts {};
    ts.f();

    D1 d1 {};
    d1.name();

    D2 d2 {};
    d2.name();

    return 0;
}
