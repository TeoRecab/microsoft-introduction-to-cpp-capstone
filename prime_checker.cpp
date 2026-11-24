#include "utils.h"

#include <cmath>
#include <iostream>
#include <limits>

bool PrimeNumberChecker() {
  auto l_max = std::numeric_limits<long>::max();
  std::string input_line;
  unsigned long n = 0;
  bool is_prime = true;

  std::cout << "\n********** Prime Number Checker **********\n";
  std::cout
      << "This utility takes an integer and informs its prime factors(other than "
         "1 and the number itself). If no factors are found, the number is a prime.\n"
         "Please provide a positive integer greater than 1, up to"
      << l_max
      << ". or write 'exit' to "
         "return to the main menu.\n\n"
      << std::endl;

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  while (true) {
    std::getline(std::cin, input_line);
    if (input_line == "exit") {
      return false; // exit order
    }
    if ((n = *ParseValidLong(input_line)) && n > 1) {
      break; // exit loop on valid number
    } else {
      std::cout << "INVALID INPUT, please try again.\n";
    }
  }

  if (n % 2 == 0) {
    std::cout << n << " is divisible by 2. It is an even number" << std::endl;
    is_prime = false;
  }

  unsigned long limit = static_cast<unsigned long>(std::sqrt(static_cast<double>(n)));
  for (unsigned long i = 3; i <=limit + 1; i += 2) {
    if (n % i == 0) {
      std::cout << n << " is divisible by " << i << std::endl;
      is_prime = false;
    }
  }

  if (is_prime) {
    std::cout << n << " is a prime.\n\n" << std::endl;
  } else {
    std::cout << n << " is not a prime.\n\n" << std::endl;
  }

  return true;
}
