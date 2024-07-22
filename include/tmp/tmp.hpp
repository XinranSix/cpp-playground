#pragma once

template <typename T, T Value>
struct integral_constant {
    static constexpr T value = Value;

    using value_type = T;
    using type = integral_constant;

    constexpr operator value_type() const noexcept { return value; }

    [[nodiscard]] constexpr value_type operator()() const noexcept {
        return value;
    }
};

template <bool Value>
using bool_constant = integral_constant<bool, Value>;

using true_type = bool_constant<true>;
using false_type = bool_constant<false>;

template <bool Test, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
    using type = T;
};

template <bool Test, typename T = void>
using enable_if_t = typename enable_if<Test, T>::type;

template <bool Test, typename T1, typename T2>
struct conditional { // type is T1 if Test is true, T2 otherwise
    using type = T1;
};

template <typename T1, typename T2>
struct conditional<false, T1, T2> {
    using type = T2;
};

template <bool Test, typename T1, typename T2>
using conditional_t = typename conditional<Test, T1, T2>::type;

/* template <typename, typename>
constexpr bool is_same_v = false;

template <typename T>
constexpr bool is_same_v<T, T> = true;

template <typename T1, typename T2>
struct is_same : bool_constant<is_same_v<T1, T2>> {};
 */
template <typename, typename>
struct is_same : false_type {};

template <typename T>
struct is_same<T, T> : true_type {};

template <typename T1, typename T2>
constexpr bool is_same_v = is_same<T1, T2>::value;

template <typename T>
struct remove_const {
    using type = T;
};

template <typename T>
struct remove_const<const T> {
    using type = T;
};

template <typename T>
using remove_const_t = typename remove_const<T>::type;

template <typename T>
struct remove_volatile {
    using type = T;
};

template <typename T>
struct remove_volatile<volatile T> {
    using type = T;
};

template <typename T>
using remove_volatile_t = typename remove_volatile<T>::type;

template <typename T>
struct remove_cv { // remove top-level const and volatile qualifiers
    using type = T;

    /* template <template <typename> typename F>
    using apply = F<T>; // apply cv-qualifiers from the class template argument
                        // to F<T> */
};

template <typename T>
struct remove_cv<const T> {
    using type = T;

    /* template <template <typename> typename F>
    using apply = F<T>; */
};

template <typename T>
struct remove_cv<volatile T> {
    using type = T;

    /* template <template <typename> typename F>
    using apply = F<T>; */
};

template <typename T>
struct remove_cv<const volatile T> {
    using type = T;

    /* template <template <typename> typename F>
    using apply = F<T>; */
};

template <typename T>
using remove_cv_t = typename remove_cv<T>::type;

template <bool First_Value, class First, class... Rest>
struct Disjunction { // handle true trait or last trait
    using type = First;
};

template <class False, class Next, class... Rest>
struct Disjunction<false, False, Next,
                   Rest...> { // first trait is false, try the next trait
    using type = typename Disjunction<Next::value, Next, Rest...>::type;
};

template <class... Traits>
struct disjunction : false_type {}; // If _Traits is empty, false_type

template <class First, class... Rest>
struct disjunction<First, Rest...>
    : Disjunction<First::value, First, Rest...>::type {
    // the first true trait in _Traits, or the last trait if none are true
};

template <class... _Traits>
constexpr bool disjunction_v = disjunction<_Traits...>::value;

template <typename T, typename... Types>
constexpr bool is_any_of_v = (is_same_v<T, Types> || ...);

// _NODISCARD constexpr bool _Is_constant_evaluated() noexcept { // Internal
// function for any standard mode
//     return __builtin_is_constant_evaluated();
// }

// #if _HAS_CXX20
// _EXPORT_STD _NODISCARD constexpr bool is_constant_evaluated() noexcept {
//     return __builtin_is_constant_evaluated();
// }
// #endif // _HAS_CXX20

template <typename T>
constexpr bool is_integral_v =
    is_any_of_v<remove_cv_t<T>, bool, char, signed char, unsigned char, wchar_t,
                char16_t, char32_t, short, unsigned short, int, unsigned int,
                long, unsigned long, long long, unsigned long long>;

template <typename T>
struct is_integral : bool_constant<is_integral_v<T>> {};

template <typename T>
constexpr bool is_floating_point_v =
    is_any_of_v<remove_cv_t<T>, float, double, long double>;

template <typename T>
struct is_floating_point : bool_constant<is_floating_point_v<T>> {};

template <typename T>
constexpr bool is_arithmetic_v = is_integral_v<T> || is_floating_point_v<T>;

template <typename T>
struct is_arithmetic : bool_constant<is_arithmetic_v<T>> {};

template <typename T>
struct remove_reference {
    using type = T;
    // using const_thru_ref_type = const T;
};

template <typename T>
struct remove_reference<T&> {
    using type = T;
    // using const_thru_ref_type = const T&;
};

template <typename T>
struct remove_reference<T&&> {
    using type = T;
    // using const_thru_ref_type = const T&&;
};

template <typename T>
using remove_reference_t = typename remove_reference<T>::type;

/* template <typename T>
using const_thru_ref = typename remove_reference<T>::const_thru_ref_type; */

template <typename T>
using remove_cvref_t = remove_cv_t<remove_reference_t<T>>;

template <typename T>
struct remove_cvref {
    using type = remove_reference_t<T>;
};
