#include <iomanip>
#include <iostream>

int main() {

  // -----------------
  // -   PROBLEM 1   -
  // -----------------

  std::cout << "\n\n";
  std::cout << "-----------------\n";
  std::cout << "-   PROBLEM 1   -\n";
  std::cout << "-----------------\n";

  float eps_f = 1.0f;
  while (1.0f + eps_f > 1.0f) {
    eps_f /= 2.0f;
  }
  eps_f *= 2.0f; // Go back to the last usable value

  double eps_d = 1.0;
  while (1.0 + eps_d > 1.0) {
    eps_d /= 2.0;
  }
  eps_d *= 2.0;

  std::cout << std::setprecision(50) << "\n";

  std::cout << "--- METHOD 1 ---\n";
  std::cout << "1 + ε > 1 → ε = ε / 2\n\n";
  std::cout << "Single precision (float) machine epsilon:    " << eps_f << "\n";
  std::cout << "Double precision (double) machine precision: " << eps_d << "\n"
            << std::endl;

  std::cout << "Single precision (float) size:  " << sizeof(float) << "\n";
  std::cout << "Double precision (double) size: " << sizeof(double) << "\n\n"
            << std::endl;

  // following the hint
  float eps_f2 = 0.0f;
  for (int j = 0; j < 100; ++j) {
    float delta = 1.0f - (1.0f + powf(2.0f, -j));
    if (delta != 0.0f) {
      eps_f2 = powf(2.0f, -j);
    } else {
      break;
    }
  }

  double eps_d2 = 0.0;
  for (int j = 0; j < 100; ++j) {
    double delta = 1.0 - (1.0 + pow(2.0, -j));
    if (delta != 0.0) {
      eps_d2 = pow(2.0, -j);
    } else {
      break;
    }
  }

  std::cout << "--- METHOD 2---\n";
  std::cout << "loop 𝛿 = 1 - (1 + 1 / 2^j)\n";
  std::cout << "end when 𝛿 ≠ 0.\n\n";
  std::cout << "Single precision (float) machine epsilon:    " << eps_f2
            << "\n";
  std::cout << "Double precision (double) machine precision: " << eps_d2 << "\n"
            << std::endl;

  std::cout << "Single precision (float) size:  " << sizeof(float) << "\n";
  std::cout << "Double precision (double) size: " << sizeof(double)
            << std::endl;

  // -----------------
  // -   PROBLEM 3   -
  // -----------------

  std::cout << "\n\n";
  std::cout << "-----------------\n";
  std::cout << "-   PROBLEM 3   -\n";
  std::cout << "-----------------\n\n";

  int a, b, c, d;
  a = 200;
  b = 300;
  c = 400;
  d = 500;

  int product_int = a * b * c * d;
  long long product_ll = static_cast<long long>(a) * b * c * d;

  std::cout << "int result (overflowed): " << product_int << "\n";
  std::cout << "long long result:        " << product_ll << "\n \n";

  std::cout << std::numeric_limits<int>::digits << "\n";
  std::cout << pow(2.0, 31) - 1 << "\n \n";

  // -----------------
  // -   PROBLEM 4   -
  // -----------------

  std::cout << "\n\n";
  std::cout << "-----------------\n";
  std::cout << "-   PROBLEM 4   -\n";
  std::cout << "-----------------\n\n";

  unsigned int counter = 0;
  for (int i = 0; i < 3; ++i)
    --counter;

  std::cout << "counter:  " << counter << "\n \n";
  return 0;
}