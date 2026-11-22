#include "utils.h"

#include <iostream>
#include <string>

void Count(const std::string &s, size_t &words, size_t &all_chars,
           size_t &non_space_chars);

bool WordAndCharacterCounter() {
  std::string text;
  size_t words, all_chars, non_space_chars;
  std::cout << "\n********** Word and Character Counter **********";
  std::cout << "\nThis utility will count words and characters of the text you "
               "pass now."
            << std::endl;

  std::cin.ignore();
  std::getline(std::cin, text);

  words = 0;
  all_chars = 0;
  non_space_chars = 0;
  Count(text, words, all_chars, non_space_chars);

  std::cout << "Amount of words: " << words << "\n";
  std::cout << "Amount of characters: " << all_chars << "\n";
  std::cout << "Amount of non-whitespace characters: " << non_space_chars
            << "\n\n" << std::endl;

  return true;
}

void Count(const std::string &s, size_t &words, size_t &all_chars,
           size_t &non_space_chars) {
  // totality of characters is size of the string
  all_chars = s.length();

  // count words by finding ends of spaces
  bool inside_word = false;
  for (char c : s) {
    if (std::isspace(c)) {
      inside_word = false;
    } else { // non-white char
      non_space_chars++;
      if (!inside_word) { // char is word start
        inside_word = true;
        words++;
      }
    }
  }
}
