#include <print>

template <typename Derived>
class Base {
public:
    void addWater(int n) { static_cast<Derived*>(this)->impl(n); }
};

class X : public Base<X> {
    friend Base<X>;

private:
    void impl(int n) const { std::println("X 设备加了 {} 毫升水", n); }
};

class Y : public Base<Y> {
    friend Base<Y>;

private:
    void impl(int n) const { std::println("Y 设备加了 {} 毫升水", n); }
};

int main(int argc, char* argv[]) {

    X x;
    x.addWater(100);

    Y y;
    y.addWater(100);

    return 0;
}
