#include <tuple>
#include <type_traits>

template <typename T>
struct remove_pointer;

template <typename T>
struct remove_pointer<T *> {
    using type = T;
};

template <typename T>
struct remove_const;

template <typename T>
struct remove_const<const T> {
    using type = T;
};

bool foo(int) { return {}; }

template <typename T>
struct function_traits;

template <typename Ret, typename... Param>
struct function_traits<Ret (*)(Param...)> {
    using return_type = Ret;
    using param_type = std::tuple<Param...>;
    static constexpr bool is_class = false;
};

template <typename Ret, typename Class, typename... Param>
struct function_traits<Ret (Class::*)(Param...)> {
    using return_type = Ret;
    using param_type = std::tuple<Param...>;
    using class_type = Class;
    static constexpr bool is_class = true;
};

template <typename T>
struct variable_traits {
    using type = T;
    static constexpr bool is_class = false;
};

template <typename T, typename Class>
struct variable_traits<T(Class::*)> {
    using type = T;
    using class_type = Class;
    static constexpr bool is_class = true;
};

struct Person {
    bool is_female() { return {}; }

    bool is_female_const() const { return {}; }

    float height;
};

template <typename T>
struct TypeInfo;

#define BEGIN_CLASS(T)                                                         \
    template <>                                                                \
    struct TypeInfo<T> {                                                       \
        using type = T;

#define FUNCTIONS(...) using functions = std::tuple<__VA_ARGS__>;

#define END_CLASS()                                                            \
    }                                                                          \
    ;

BEGIN_CLASS(Person)
FUNCTIONS(function_traits<decltype(&Person::is_female)>,
          function_traits<decltype(&Person::is_female_const)>)
END_CLASS()

int main(int argc, char *argv[]) {
    {
        using type1 = remove_pointer<int *>::type;
        using type2 = remove_const<const int>::type;

        auto ptr = &foo;
        using function_info = function_traits<decltype(ptr)>;
        using return_type = function_info::return_type;
        using param_type = function_info::param_type;

        static_assert(std::is_same_v<return_type, bool>, "");
        static_assert(std::is_same_v<param_type, std::tuple<int>>, "");
    }

    {
        using function_info = function_traits<decltype(&Person::is_female)>;
        using param_type = function_info::param_type;

        /* bool (Person::*p)() const = &Person::is_female_const;
        float(Person::*ptr) = &Person::height; */
    }

    { using type = TypeInfo<Person>; }

    return 0;
}
