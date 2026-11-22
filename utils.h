#pragma once

#include <optional>
#include <string>
#include <vector>

bool WordAndCharacterCounter();
bool StatisticalCalculator();
bool SimpleFileInfo();
bool DateDifferenceCalculator();

//from other_turils.cpp (many files need this)
std::optional<short> ParseValidInput(const std::string& input);
