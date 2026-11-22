#include "utils.h"

#include <optional>
#include <charconv>

std::optional<short> ParseValidInput(const std::string &input) {
  short n;
  auto [ptr, ec] =
      std::from_chars(input.data(), input.data() + input.size(), n);
  if (ec == std::errc{} && ptr == input.data() + input.size()) {
    return n;
  }
  return std::nullopt;
}


std::optional<double> ParseValidDouble(const std::string &input) {
  double n;
  auto [ptr, ec] =
      std::from_chars(input.data(), input.data() + input.size(), n);
  if (ec == std::errc{} && ptr == input.data() + input.size()) {
    return n;
  }
  return std::nullopt;
}
