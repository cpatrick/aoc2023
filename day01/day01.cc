#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"

ABSL_FLAG(std::string, input, "input.txt", "input text file");

bool isNumber(char c)
{
  return c >= '0' && c <= '9';
}

int getCalibrationNumber(std::string line)
{
  std::vector<int> numbers = {};
  for (char c : line)
  {
    if (isNumber(c))
    {
      numbers.push_back(c - '0');
    }
  }
  return numbers.front() * 10 + numbers.back();
}

int getRealCalibrationNumber(std::string line)
{
  std::map<std::string, int> numbers = {{"0", 0},
                                        {"1", 1},
                                        {"2", 2},
                                        {"3", 3},
                                        {"4", 4},
                                        {"5", 5},
                                        {"6", 6},
                                        {"7", 7},
                                        {"8", 8},
                                        {"9", 9},
                                        {"zero", 0},
                                        {"one", 1},
                                        {"two", 2},
                                        {"three", 3},
                                        {"four", 4},
                                        {"five", 5},
                                        {"six", 6},
                                        {"seven", 7},
                                        {"eight", 8},
                                        {"nine", 9}};
  std::map<size_t, int> foundNumbers;
  for (auto const &iter : numbers)
  {
    auto key = iter.first;
    auto val = iter.second;
    // Find first and then last occurances
    auto found = line.find(key);
    if (found != std::string::npos)
    {
      foundNumbers[found] = val;
    }
    found = line.rfind(key);
    if (found != std::string::npos)
    {
      foundNumbers[found] = val;
    }
  }
  return foundNumbers.begin()->second * 10 + foundNumbers.rbegin()->second;
}

int main(int argc, char **argv)
{
  absl::ParseCommandLine(argc, argv);

  auto inputPath = absl::GetFlag(FLAGS_input);
  std::ifstream inputFile;
  inputFile.open(inputPath);
  int sum = 0;
  int realSum = 0;
  if (inputFile.is_open())
  {
    std::string line;
    while (std::getline(inputFile, line))
    {
      sum += getCalibrationNumber(line);
      realSum += getRealCalibrationNumber(line);
    }

    inputFile.close();
  }
  else
  {
    // If the file is not open, print an error message
    std::cout << "Error opening file: " << inputPath << std::endl;
  }

  std::cout << "Part 1 solution: " << sum << std::endl;
  std::cout << "Part 2 solution: " << realSum << std::endl;

  return 0;
}
