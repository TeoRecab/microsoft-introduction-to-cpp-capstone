#include "utils.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

// functions
void CalculateMeans(const std::vector<double> &v, double &ari_mean,
                    double &geo_mean, double &har_mean);
void CalculateMedianAndMode(const std::vector<double> &v, const double &mean,
                            double &median, double &mode);
double CalculateStandardDeviation(const std::vector<double> &v, double &mean);

bool StatisticalCalculator() {
  auto d_min = std::numeric_limits<double>::lowest;
  auto d_max = std::numeric_limits<double>::max();
  std::string input_line;
  double sample;
  std::vector<double> samples;

  std::cout << "\n********** Statistical Calculator **********";
  std::cout
      << "\nThis utility takes a series of numbers, sorts it and gives the "
         "mean "
         "(average), geometric, mean, harmonic mean, median (The most middling "
         "value), mode (the most common value), and standard deviation."
         "Please provide the first number to consider or write 'exit' to "
         "return to the main menu."
         "(The program will accept numbers between "
      << d_min << " and " << d_max << " with 15 significant figures)"
      << std::endl;

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  // get samples from input
  // loop for input until exit order or done order
  while (true) {
    std::getline(std::cin, input_line);
    if (input_line == "exit") {
      return false; // exit order
    }
    if (input_line == "done") {
      break; // "samples is complete" order
    }
    if ((sample = *ParseValidDouble(input_line))) {
      samples.push_back(sample);
      std::cout << "Taken the value: " << sample;
    } else {
      std::cout << "INVALID INPUT, number not taken";
    }
    std::cout << ". \nWrite another value, 'done' to execute the calculationsor "
       "'exit' to return to the main menu."
    << std::endl;
  }

  // do the math
  std::sort(samples.begin(), samples.end());

  double ari_mean = 0, geo_mean = 1, har_mean = 0;
  CalculateMeans(samples, ari_mean, geo_mean, har_mean);

  double std_dev = 0;
  std_dev = CalculateStandardDeviation(samples, ari_mean);

  double median = 0, mode = 0;
  CalculateMedianAndMode(samples, ari_mean, median, mode);

  // print results
  std::cout << "\nThe sorted values are:\n";
  for (size_t i = 0; i < samples.size(); i++) {
    std::cout << i + 1 << ": " << samples[i] << ",\n";
  }
  std::cout << "\nThe arithmetic mean is: " << ari_mean << "\n";
  std::cout << "The geometric mean is: " << geo_mean << "\n";
  std::cout << "The harmonic mean is: " << har_mean << "\n";
  std::cout << "The madian is: " << median << "\n";
  std::cout << "The mode is: " << median << "\n";
  std::cout << "The standard deviation is: " << std_dev << "\n\n" << std::endl;

  return true;
}

void CalculateMeans(const std::vector<double> &v, double &ari_mean,
                    double &geo_mean, double &har_mean) {
  double har_divisor = 0;

  for (size_t i = 0; i < v.size(); i++) {
    // arithmetic step
    ari_mean += v[i] / static_cast<double>(
                           v.size()); // divide on each add to prevent overflows

    // geometric step
    geo_mean *= std::pow(v[i], 1.0 / static_cast<double>(v.size()));

    // harmonic step
    if (v[i] != 0) {
      har_divisor += 1.0 / v[i];
    } else {
      // any zero in the samples makes the harmonic mean zero
      har_divisor = std::numeric_limits<double>::infinity();
    }
  }
  // harmonic end
  har_mean = static_cast<double>(v.size()) / har_divisor;

  return;
}

double CalculateStandardDeviation(const std::vector<double> &v, double &mean) {
  double deviation = 0;

  for (const double &n : v) {
    deviation += pow(n - mean, 2) / static_cast<double>(v.size());
  }

  deviation = sqrt(deviation);
  return deviation;
}
void CalculateMedianAndMode(const std::vector<double> &v, const double &mean,
                            double &median, double &mode) {
  size_t best_count = 0;
  size_t run = 0;

  for (size_t i = 0; i < v.size(); ++i) {
    run = (i > 0 && v[i] == v[i - 1]) ? run + 1 : 1;
    if (run > best_count ||
        run == best_count && (std::abs(v[i] - mean) < std::abs(mode - mean))) {
      best_count = run;
      mode = v[i];
    }
  }

  size_t mid = v.size() / 2;
  median = (v.size() % 2 == 0)
               ? (static_cast<double>(v[mid - 1]) + v[mid]) / 2.0
               : v[mid];
  return;
}
