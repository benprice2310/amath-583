#include <iostream>

namespace amath483 {
    double pi = 3.14159;
};

namespace amath583 {
    double pi = 3.14;
};

using namespace amath483;

int main() {
    std::cout << "\n\nThe legislated value of pi is ";
    std::cout << pi << "\n\n" << std::endl;
    

    return 0;
}