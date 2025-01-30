#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char **argv)
{
  std::ifstream inputFile;

  // Ensure right usage
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " FILE" << std::endl;
    return EXIT_FAILURE;
  } else {
    inputFile.open(argv[1]);
    if (!inputFile) {
      std::cerr << "Error opening " << argv[1] << std::endl;
      return EXIT_FAILURE;
    }
  }

  inputFile >> std::noskipws;

  std::vector<std::string> fileContents;
  std::string buffer;

  while (std::getline(inputFile, buffer)) {
    fileContents.push_back(buffer);
  }

  unsigned nLine = fileContents.size(), nChar = 0, nWspace = 0, nEmptyLine = 0;
  for (const auto &line : fileContents) {
    if (line.empty()) {
      nEmptyLine++;
      continue;
    }

    for (const auto &c : line) {
      if (std::isspace(c))
        nWspace++;
      else
        nChar++;
    }
  }

  nWspace += nLine - 1;

  std::cout << "Line count: " << nLine << " (incl. " << nEmptyLine
            << " empty lines)\nCharacter count (incl. whitespaces): " << nChar + nWspace
            << "\nWhitespace count: " << nWspace << std::endl;

  return EXIT_SUCCESS;
}
