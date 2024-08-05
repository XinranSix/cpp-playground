#include <iostream>

#include <magic_enum.hpp>

enum class Language : int {
    日本語 = 10,
    한국어 = 20,
    English = 30,
    😃 = 40,
};

int main() {
    std::cout << magic_enum::enum_name(Language::日本語)
              << std::endl; // Japanese
    std::cout << magic_enum::enum_name(Language::한국어) << std::endl; // Korean
    std::cout << magic_enum::enum_name(Language::English)
              << std::endl;                                        // English
    std::cout << magic_enum::enum_name(Language::😃) << std::endl; // Emoji

    std::cout << std::boolalpha;
    std::cout << (magic_enum::enum_cast<Language>("日本語").value() ==
                  Language::日本語)
              << std::endl; // true

    return 0;
}
