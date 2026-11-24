/* capstone project
 * DONE: word and character counter
 *        seems to work <- using std::getline
 * DONE: statistical calculator
 * DONE: simple file info utility
 * TODO: prime number checker
 */

#include "utils.h"

#include <iostream>
#include <optional>
#include <string>

std::optional<short> PrintMenu();

int main() {
  std::optional<short> parsed_input = std::nullopt;

  std::cout << "Welcome to the utilitApp\n Please choose an option by number:\n\n";
  bool exit = false;
  while (!exit) {
    //get a valid input from the menu
    parsed_input = PrintMenu();
    if (parsed_input) {
      switch (*parsed_input) {
      case 1:
        WordAndCharacterCounter();
        break;
      case 2:
        StatisticalCalculator();
        break;
      case 3:
        SimpleFileInfo();
        break;
      case 4:
        PrimeNumberChecker();
        break;
      case 5:
        std::cout << "exiting..." << std::endl;
        exit = true;
        break;
      }
    } else {
      std::cout << "Invalid Input, please try again...\n\n" << std::endl;
    }
  }
}

std::optional<short> PrintMenu() {

  std::cout << "1: Word and Character counter\n";
  std::cout << "2: Statistical Calculator\n";
  std::cout << "3: Simple File Info\n";
  std::cout << "4: Prime Number Checker\n";
  std::cout << "5: Exit" << std::endl;

  std::string input;
  std::cin >> input;
  return ParseValidShort(input);
}

