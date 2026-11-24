#include "utils.h"

#include <algorithm>
#include <charconv>
#include <chrono>
#include <filesystem>
#include <format>
#include <iostream>
#include <unordered_map>

namespace fs = std::filesystem;

void DisplayFileType(fs::path file_str);

bool SimpleFileInfo() {
  std::cout << "\n********** Simple File Information**********";
  std::cout << "\nThis utility will inform of a file's last used date, "
               "permissions, type and size. \nPlease enter a file path or "
               "'exit' to return to the main menu."
            << std::endl;

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::string path_to_file;
  std::error_code ec;
  while (true) {
    if (!std::getline(std::cin, path_to_file) || path_to_file == "exit") {
      return false;
    }

    if (fs::is_regular_file(path_to_file, ec))
      break; // exit loop on success

    std::cerr << "\"" << path_to_file << "\" is not a regular file.\n "
              << "Try again or type 'exit' to return to the main menu.\n";
  }

  // reusable state and path
  // fs::file_status status = fs::status(path_to_file, ec);
  fs::path file_p(path_to_file);

  // display type
  DisplayFileType(file_p);

  // display size
  std::uintmax_t size = fs::file_size(path_to_file, ec);
  if (ec) {
    std::cerr << "Could not get file size: " << ec.message() << '\n';
  }
  std::cout << "Size: " << size << " bytes\n";

  // get file last touch time
  fs::file_time_type t = fs::last_write_time(file_p, ec);
  auto sys = std::chrono::clock_cast<std::chrono::system_clock>(t);
  // Display lt time
  std::cout << std::format("Last modified on: {:%Y-%m-%d %H:%M:%S}\n\n",
                           std::chrono::floor<std::chrono::seconds>(sys));

  return true;
}

void DisplayFileType(fs::path p) {

  // Extensions look up table
  const std::unordered_map<std::string, std::string> types = {
      {".txt", "Text file"},       {".md", "Markdown file"},
      {".cpp", "C++ source file"}, {".cc", "C++ source file"},
      {".h", "C/C++ header file"}, {".o", "object file. Probably build output"},
      {".hpp", "C++ header file"}, {".py", "Python script"},
      {".json", "JSON data file"}, {".png", "PNG image"},
      {".jpg", "JPG image"},       {".zip", "ZIP archive"},
      {".tar", "tar archive"},
  };

  std::string ext = p.extension().string();
  // below is to make the extension lowercase. commented out because not needed
  // but is interesting. Last arg is the lambda function to lower every
  // character std::transform(ext.begin(), ext.end(), ext.begin(),
  //                [](unsigned char c) { return
  //                static_cast<char>()std::tolower(c)); });

  auto this_ext = types.find(ext);
  if (this_ext != types.end()) {
    std::cout << "\nThis is a " << this_ext->second << ".\n";
  } else if (ext.empty()) {
    std::cout << "File has no extension\n";
  } else {
    std::cout << "Unknown file type (" << ext << ")\n";
  }
}
