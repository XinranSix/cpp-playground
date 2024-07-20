#include "fmt/base.h"
#include <string>

#include <fmt/core.h>
#include <type_traits>
#include <vector>

struct Person final {
    std::string familyName;
    float height;
    bool isFemale;

    void IntroduceMySelf() const { fmt::println("hello"); }

    bool IsFemale() const {
        fmt::println("IsFemale");
        return false;
    }

    bool GetMarried(Person &other) {
        bool success = other.isFemale != isFemale;
        if (isFemale) {
            familyName = "Mrs." + other.familyName;
        } else {
            familyName = "Mr." + other.familyName;
        }
        return success;
    }

    void OutputInt(int i) { fmt::println("{}", i); }
};

class Type {
public:
    virtual ~Type() = default;

    Type(const std::string &name) : name_ { name } {}

    auto &GetName() const { return name_; }

private:
    std::string name_;
};

class Numeric : public Type {
public:
    enum class Kind {
        Unknown,
        Int8,
        Int16,
        Int32,
        Int64,
        Int128,
        Float,
        Double,
    };

    Numeric(Kind kind, bool isSigned)
        : Type { getName(kind) }, kind_ { kind }, isSigned_ { isSigned } {}

    auto GetKind() const { return kind_; }
    auto IsSigned() const { return isSigned_; }

    template <typename T>
    static Numeric Create() {
        return Numeric { detectKind<T>(), std::is_signed_v<T> };
    }

private:
    Kind kind_;
    bool isSigned_;

    static std::string getName(Kind kind) {
        switch (kind) {
        case Kind::Int8: return "int8";
        case Kind::Int16: return "int16";
        case Kind::Int32: return "int32";
        case Kind::Int64: return "int64";
        case Kind::Int128: return "int128";
        case Kind::Float: return "float";
        case Kind::Double: return "double";
        default: break;
        }

        return "Unknown";
    }

    template <typename T>
    static Kind detectKind() {
        if constexpr (std::is_same_v<T, char>) {
            return Kind::Int8;
        } else if constexpr (std::is_same_v<T, short>) {
            return Kind::Int16;
        } else if constexpr (std::is_same_v<T, int>) {
            return Kind::Int32;
        } else if constexpr (std::is_same_v<T, long>) {
            return Kind::Int64;
        } else if constexpr (std::is_same_v<T, long long>) {
            return Kind::Int128;
        } else if constexpr (std::is_same_v<T, float>) {
            return Kind::Float;
        } else if constexpr (std::is_same_v<T, double>) {
            return Kind::Double;
        } else {
            return Kind::Unknown;
        }
    }
};

class Enum : public Type {
public:
    struct Item {
        using value_type = long;

        std::string name;
        value_type value;
    };

    Enum(const std::string &name) : Type { name } {}

    template <typename T>
    void Add(const std::string &name, T value) {
        items_.emplace_back(
            Item { name, static_cast<typename Item::value_type>(value) });
    }

    auto &GetItems() const { return items_; }

private:
    std::vector<Item> items_;
};

class Class : public Type {
public:
private:
};

int main(int argc, char *argv[]) {

    fmt::println("{}", std::is_same_v<int, int32_t>);
    fmt::println("{}", std::is_same_v<char, int8_t>);
    fmt::println("{}", std::is_same_v<char, uint8_t>);

    return 0;
}
