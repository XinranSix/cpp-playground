#include <cstdint>

#include <catch2/benchmark/catch_benchmark_all.hpp>
#include <catch2/catch_test_macros.hpp>
#include <fmt/core.h>

int add_(int a, int b) { return a + b; }
int add(int a, int b) { throw; }

TEST_CASE("add 3 and 4 is 7(success)", "anything") {
    REQUIRE(add_(3, 4) == 7);
    REQUIRE_FALSE(add_(3, 4) == 8);
    REQUIRE_NOTHROW(add_(1, 2));
    // REQUIRE_THROWS(add(1, 2));
    // REQUIRE_THROWS_AS(add(1, 2), std::exception);
}

int factorial(int n) { return n <= 1 ? 1 : factorial(n - 1) * n; }

TEST_CASE("Factorial of 1 and higher are computed (pass)", "[single-file]") {
    REQUIRE(factorial(1) == 1);
    REQUIRE(factorial(2) == 2);
    REQUIRE(factorial(3) == 6);
    REQUIRE(factorial(10) == 3628800);
}

TEST_CASE("Factorial of 1 and higher are computed (pass)", "[check]") {
    CHECK(factorial(1) == 1);
    CHECK(factorial(2) == 2);
    CHECK(factorial(3) == 6);
    CHECK(factorial(10) == 3628800);
}

std::uint64_t fibonacci(std::uint64_t n) {
    return n < 2 ? 1 : factorial(n - 1) + factorial(n - 2);
}

TEST_CASE("Fibonacci") {
    CHECK(fibonacci(0) == 1);
    CHECK(fibonacci(5) == 30);

    BENCHMARK("Fibonacci 20") { return fibonacci(20); };

    BENCHMARK("Fibonacci 25") { return fibonacci(25); };
}
