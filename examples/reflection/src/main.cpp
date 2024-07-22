#include <cassert>
#include <list>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include <fmt/core.h>

#include "fmt/base.h"
#include "function_traits.hpp"
#include "variable_traits.hpp"

struct Person final {
    std::string familyName;
    float height;
    bool isFemale;

    Person() = default;

    Person(const Person& p)
        : familyName { p.familyName }, height { p.height },
          isFemale { p.isFemale } {
        fmt::println("person copied");
    }

    Person(Person&& p)
        : familyName { std::move(p.familyName) },
          height { std::move(p.height) }, isFemale { std::move(p.isFemale) } {
        fmt::println("person steal");
    }

    ~Person() { fmt::println("person released"); }

    void IntroduceMySelf() const { fmt::println("hello"); }

    bool IsFemale() const {
        fmt::println("IsFemale");
        return false;
    }

    bool GetMarried(Person& other) {
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

class Numeric;
class Enum;
class Class;
class Type;

std::list<const Type*> gTypeList;

class Type {
public:
    template <typename T>
    friend class EnumFactory;

    template <typename T>
    friend class ClassFactory;

    enum class Kind { Numeric, Enum, Class };

    virtual ~Type() = default;

    Type(const std::string& name, Kind kind) : name_ { name }, kind_ { kind } {}

    auto& GetName() const { return name_; }
    auto GetKind() const { return kind_; }

    const Numeric* AsNumeric() const {
        if (kind_ == Kind::Numeric) {
            return (const Numeric*)(this);
        } else {
            return nullptr;
        }
    }

    const Enum* AsEnum() const {
        if (kind_ == Kind::Enum) {
            return (const Enum*)(this);
        } else {
            return nullptr;
        }
    }

    const Class* AsClass() const {
        if (kind_ == Kind::Class) {
            return (const Class*)(this);
        } else {
            return nullptr;
        }
    }

private:
    std::string name_;
    Kind kind_;
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
        : Type { getName(kind), Type::Kind::Numeric }, kind_ { kind },
          isSigned_ { isSigned } {}

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

    Enum() : Type { "Unknown-Enum", Type::Kind::Enum } {}
    Enum(const std::string& name) : Type { name, Type::Kind::Enum } {}

    template <typename T>
    void Add(const std::string& name, T value) {
        items_.emplace_back(
            Item { name, static_cast<typename Item::value_type>(value) });
    }

    auto& GetItems() const { return items_; }

private:
    std::vector<Item> items_;
};

struct MemberVariable {
    std::string name;
    const Type* type;

    template <typename T>
    static MemberVariable Create(const std::string& name);
};

struct MemberFunction {
    std::string name;
    const Type* retType;
    std::vector<const Type*> paramTypes;

    template <typename T>
    static MemberFunction Create(const std::string& name);

private:
    template <typename Params, size_t... Idx>
    static std::vector<const Type*>
        cvtTypelist2Vector(std::index_sequence<Idx...>);
};

class Class : public Type {
public:
    Class() : Type { "Unknown-Class", Type::Kind::Class } {}
    Class(const std::string& name) : Type { name, Type::Kind::Class } {}

    void AddVar(MemberVariable&& var) { vars_.emplace_back(std::move(var)); }

    void AddFunc(MemberFunction&& func) {
        funcs_.emplace_back(std::move(func));
    }

    auto& GetVariables() const { return vars_; }
    auto& GetFunctions() const { return funcs_; }

private:
    std::vector<MemberVariable> vars_;
    std::vector<MemberFunction> funcs_;
};

template <typename T>
class NumericFactory final {
public:
    static NumericFactory& Instance() {
        static NumericFactory inst { Numeric::Create<T>() };
        static bool isSaved = false;
        if (!isSaved) {
            gTypeList.push_back(&inst.Info());
            isSaved = true;
        }
        return inst;
    }

    auto& Info() const { return info_; }

private:
    Numeric info_;

    NumericFactory(Numeric&& info) : info_ { std::move(info) } {}
};

template <typename T>
class EnumFactory final {
public:
    static EnumFactory& Instance() {
        static EnumFactory inst;
        static bool isSaved = false;
        if (!isSaved) {
            gTypeList.push_back(&inst.Info());
            isSaved = true;
        }
        return inst;
    }

    auto& Info() const { return info_; }

    EnumFactory& Regist(const std::string& name) {
        info_.name_ = name;
        return *this;
    }

    template <typename U>
    EnumFactory& Add(const std::string& name, U value) {
        info_.Add(name, value);
        return *this;
    }

    void Unregist() { info_ = {}; }

private:
    Enum info_;
};

template <typename T>
class ClassFactory final {
public:
    static ClassFactory& Instance() {
        static ClassFactory inst;
        static bool isSaved = false;
        if (!isSaved) {
            gTypeList.push_back(&inst.Info());
            isSaved = true;
        }
        return inst;
    }

    auto& Info() const { return info_; }

    ClassFactory& Regist(const std::string& name) {
        info_.name_ = name;
        return *this;
    }

    template <typename U>
    ClassFactory& AddVariable(const std::string& name) {
        info_.AddVar(MemberVariable::Create<U>(name));
        return *this;
    }

    template <typename U>
    ClassFactory& AddFunction(const std::string& name) {
        info_.AddFunc(MemberFunction::Create<U>(name));
        return *this;
    }

    void Unregist() { info_ = Class {}; }

private:
    Class info_;
};

class TrivialFactory {
public:
    static TrivialFactory& Instance() {
        static TrivialFactory inst;
        return inst;
    }
};

template <typename T>
class Factory final {
public:
    static auto& GetFactory() {
        using type = std::remove_reference_t<T>;

        if constexpr (std::is_fundamental_v<type>) {
            return NumericFactory<type>::Instance();
        } else if constexpr (std::is_enum_v<type>) {
            return EnumFactory<type>::Instance();
        } else if constexpr (std::is_class_v<type>) {
            return ClassFactory<type>::Instance();
        } else {
            return TrivialFactory::Instance();
        }
    }
};

template <typename T>
auto& Registrar() {
    return Factory<T>::GetFactory();
}

template <typename T>
const Type* GetType() {
    return &Factory<T>::GetFactory().Info();
}

const Type* GetType(const std::string& name) {
    for (auto typeinfo : gTypeList) {
        if (typeinfo->GetName() == name) {
            return typeinfo;
        }
    }
    return nullptr;
}

enum class MyEnum { Value1 = 1, Value2 = 2 };

template <typename T>
MemberVariable MemberVariable::Create(const std::string& name) {
    using type = typename variable_traits<T>::type;
    return MemberVariable { name, GetType<type>() };
}

template <typename T>
MemberFunction MemberFunction::Create(const std::string& name) {
    using traits = function_traits<T>;
    using args = typename traits::args;
    return MemberFunction {
        name, GetType<typename traits::return_type>(),
        cvtTypelist2Vector<args>(
            std::make_index_sequence<std::tuple_size_v<args>>())
    };
}

template <typename Params, size_t... Idx>
std::vector<const Type*>
MemberFunction::cvtTypelist2Vector(std::index_sequence<Idx...>) {
    return { GetType<std::tuple_element_t<Idx, Params>>()... };
}
class any;

template <typename T>
any make_copy(const T&);

template <typename T>
any make_steal(T&&);

template <typename T>
any make_ref(T&);

template <typename T>
any make_cref(const T&);

class any final {
public:
    enum class storage_type { Empty, Copy, Steal, Ref, ConstRef };

    struct operations {
        any (*copy)(const any&) = {};
        any (*steal)(any&) = {};
        void (*release)(any&) = {};
    };

    any() = default;

    any(const any& o)
        : typeinfo { o.typeinfo }, store_type(o.store_type), ops { o.ops } {
        if (ops.copy) {
            auto new_any = ops.copy(o);
            payload = new_any.payload;
            new_any.payload = nullptr;
            new_any.ops.release = nullptr;
        } else {
            store_type = storage_type::Empty;
            typeinfo = nullptr;
        }
    }

    any(any&& o)
        : typeinfo { std::move(o.typeinfo) }, payload { std::move(o.payload) },
          store_type { std::move(o.store_type) }, ops { std::move(o.ops) } {}

    any& operator=(const any& o) {
        if (&o != this) {
            typeinfo = o.typeinfo;
            store_type = o.store_type;
            ops = o.ops;
            if (ops.copy) {
                auto new_any = ops.copy(o);
                payload = new_any.payload;
                new_any.payload = nullptr;
                new_any.ops.release = nullptr;
            } else {
                store_type = storage_type::Empty;
                typeinfo = nullptr;
            }
        } else {
            store_type = storage_type::Empty;
            typeinfo = nullptr;
        }
        return *this;
    }

    any& operator=(any&& o) {
        if (&o != this) {
            typeinfo = std::move(o.typeinfo);
            store_type = std::move(o.store_type);
            ops = std::move(o.ops);
            payload = std::move(payload);
        }
        return *this;
    }

    ~any() {
        if (ops.release && (store_type == storage_type::Copy ||
                            store_type == storage_type::Steal)) {
            ops.release(*this);
        }
    }

    const Type* typeinfo {};
    /* union {
        char sso[1024];
        void* payload {};
    }; */
    void* payload {};
    storage_type store_type = storage_type::Empty;
    operations ops;

private:
};

template <typename T>
struct operations_traits {
    static any copy(const any& elem) {
        assert(elem.typeinfo == GetType<T>());

        any return_value;
        /* if constexpr (sizeof(T) <= 1024) {
            new (return_value.sso) T { *static_cast<T*>(elem.payload) };
        } else {
            return_value.payload = new T { *static_cast<T*>(elem.payload) };
        } */
        return_value.payload = new T { *static_cast<T*>(elem.payload) };
        return_value.typeinfo = elem.typeinfo;
        return_value.store_type = any::storage_type::Copy;
        return_value.ops = elem.ops;
        return return_value;
    }

    static any steal(any& elem) {
        assert(elem.typeinfo == GetType<T>());

        any return_value;
        return_value.payload =
            new T { std::move(*static_cast<T*>(elem.payload)) };
        return_value.typeinfo = elem.typeinfo;
        return_value.store_type = any::storage_type::Copy;
        elem.store_type = any::storage_type::Steal;
        return_value.ops = elem.ops;
        return return_value;
    }

    static void release(any& elem) {
        assert(elem.typeinfo == GetType<T>());

        delete static_cast<T*>(elem.payload);
        elem.payload = nullptr;
        elem.store_type = any::storage_type::Empty;
        elem.typeinfo = nullptr;
    }
};

template <typename T>
any make_copy(const T& elem) {
    any return_value;
    return_value.payload = new T { elem };
    return_value.typeinfo = GetType<T>();
    return_value.store_type = any::storage_type::Copy;
    if constexpr (std::is_copy_constructible_v<T>) {
        return_value.ops.copy = &operations_traits<T>::copy;
    }
    if constexpr (std::is_move_constructible_v<T>) {
        return_value.ops.steal = &operations_traits<T>::steal;
    }
    if constexpr (std::is_destructible_v<T>) {
        return_value.ops.release = &operations_traits<T>::release;
    }
    return return_value;
}

template <typename T>
any make_steal(T&& elem) {
    any return_value;
    return_value.payload = new T { std::move(elem) };
    return_value.typeinfo = GetType<T>();
    return_value.store_type = any::storage_type::Steal;
    if constexpr (std::is_copy_constructible_v<T>) {
        return_value.ops.copy = &operations_traits<T>::copy;
    }
    if constexpr (std::is_move_constructible_v<T>) {
        return_value.ops.steal = &operations_traits<T>::steal;
    }
    if constexpr (std::is_destructible_v<T>) {
        return_value.ops.release = &operations_traits<T>::release;
    }
    return return_value;
}

template <typename T>
any make_ref(T& elem) {
    any return_value;
    return_value.payload = &elem;
    return_value.typeinfo = GetType<T>();
    return_value.store_type = any::storage_type::Ref;
    if constexpr (std::is_copy_constructible_v<T>) {
        return_value.ops.copy = &operations_traits<T>::copy;
    }
    if constexpr (std::is_move_constructible_v<T>) {
        return_value.ops.steal = &operations_traits<T>::steal;
    }
    if constexpr (std::is_destructible_v<T>) {
        return_value.ops.release = &operations_traits<T>::release;
    }
    return return_value;
}

template <typename T>
any make_cref(const T& elem) {
    any return_value;
    return_value.payload = &elem;
    return_value.typeinfo = GetType<T>();
    return_value.store_type = any::storage_type::ConstRef;
    if constexpr (std::is_copy_constructible_v<T>) {
        return_value.ops.copy = &operations_traits<T>::copy;
    }
    if constexpr (std::is_move_constructible_v<T>) {
        return_value.ops.steal = &operations_traits<T>::steal;
    }
    if constexpr (std::is_destructible_v<T>) {
        return_value.ops.release = &operations_traits<T>::release;
    }
    return return_value;
}

template <typename T>
T* try_cast(any& elem) {
    if (elem.typeinfo == GetType<T>()) {
        return (T*)(elem.payload);
    } else {
        return nullptr;
    }
}

int main(int argc, char* argv[]) { return 0; }
