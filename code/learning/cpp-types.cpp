#include <iostream>
#include <cstdint> // for int8_t, etc.

int main() {
    std::cout << "Sizes of various data types (in bytes):\n";

    // integers
    std::cout << "int8_t    " << sizeof(int8_t) << "\n";
    std::cout << "int32_t   " << sizeof(int32_t) << "\n";
    std::cout << "unsigned int" << sizeof(unsigned int) << "\n";

    // floating-point
    std::cout << "float:    " << sizeof(float) << "\n";
    std::cout << "double:   " << sizeof(double) << "\n";

    // other
    std::cout << "char:     " << sizeof(char) << "\n";
    std::cout << "bool:     " << sizeof(bool) << "\n";
    std::cout << "\'\\n\':    " << sizeof('\n') << "\n";
    std::cout << "\"\\n\":    " << sizeof("\n") << "\n";

    return 0;
}