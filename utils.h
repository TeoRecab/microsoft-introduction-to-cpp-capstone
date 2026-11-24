#pragma once

#include <optional>
#include <string>
#include <vector>

bool WordAndCharacterCounter();
bool StatisticalCalculator();
bool SimpleFileInfo();
bool PrimeNumberChecker();

//from other_turils.cpp (many files need this)
std::optional<short> ParseValidShort(const std::string& input);
std::optional<unsigned long> ParseValidLong(const std::string& input);
std::optional<double> ParseValidDouble(const std::string &input);
