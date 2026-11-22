#include "utils.h"

#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <cmath>

// functions
void CalcuLateMeans(const std::vector<double> &v, double &ari_mean,
                      double &geo_mean, double &har_mean);
//TODO: median, mode and deviation calculations
double CalcuLateMedian(const std::vector<double> &v);
double CalcuLateMode(const std::vector<double> &v);
double CalcuLateStandardDeviation(const std::vector<double> &v);

bool StatisticalCalculator() {
  auto d_min = std::numeric_limits<double>::lowest;
  auto d_max = std::numeric_limits<double>::max();

  std::cout << "\n********** Statistical Calculator **********";
  std::cout
      << "\nThis utility takes a series of numbers and gives the mean "
         "(average), geometric, mean, harmonic mean, median (The most middling "
         "value), mode (the most common value), and standard deviation."
         "Please provide the first number to consider or write 'exit' to "
         "return to the main menu."
         "(The program will accept numbers between "
      << d_min << " and " << d_max << " with 15 significant figures)"
      << std::endl;

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::string input_line;
  double sample;
  std::vector<double> samples;
  // loop for input until exit order or done order
  while (true) {
    if (!std::getline(std::cin, input_line) || input_line == "exit") {
      return false; // exit order
    }
    if (input_line == "done") {
      break; // "samples is complete" order
    }
    if ((sample = *ParseValidDouble(input_line))) {
      samples.push_back(sample);
    }
    std::cout << "Taken the value: " << sample
              << ". Write another value, 'done' to execute the calculationsor "
                 "'exit' to return to the main menu."
              << std::endl;
  }

  // do the math
  double ari_mean = 0, geo_mean = 1, har_mean;
  CalcuLateMeans(samples, ari_mean, geo_mean,har_mean);

  return true;
}

void CalcuLateMeans(const std::vector<double> &v, double &ari_mean,
                      double &geo_mean, double &har_mean) {
  double har_divisor = 0;

  for (int i = 0; i < v.size(); i++) {
    //arithmetic step
    ari_mean += v[i] / v.size(); //divide on each add to prevent overflows
    
    //geometric step
    geo_mean *= std::pow(v[i], 1.0 / v.size());

    //harmonic step
    if(v[i] != 0) {
      har_divisor += 1.0 / v[i];
    } else {
      // any zero in the samples makes the harmonic mean zero
      har_divisor = std::numeric_limits<double>::infinity();
    }
  }
  //harmonic end
  har_mean = v.size() / har_divisor;

  return;
}
