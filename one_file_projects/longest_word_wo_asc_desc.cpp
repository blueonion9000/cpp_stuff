
#include <cstddef>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

bool CheckValid(const std::string &word);

const std::string asc_and_desc_chars{"qtyipdfghjklb"};

int main(int argc, char **argv)
{
  // ensure right usage
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " TOP_SIZE FILE" << std::endl;
    return EXIT_FAILURE;
  }
  if (std::stoi(argv[1]) < 1) {
    std::cerr << "Error: top size can't be less than 1." << std::endl;
    return EXIT_FAILURE;
  }
  std::ifstream input_file(argv[2], std::fstream::in);
  if (!input_file) {
    std::cerr << "File read error." << std::endl;
    return EXIT_FAILURE;
  }

  // variables
  auto top_size = std::atoi(argv[1]);
  std::string buffer;
  std::map<std::size_t, std::vector<std::string>, std::greater<std::size_t>> longest_map;

  // seek through the file, word by word
  while (input_file >> buffer) {
    if (!CheckValid(buffer))
      continue;

    // accessing inexistent key automatically creates it and
    // value-initialises the key value (which is empty
    // string vector in our case)
    auto &words_with_size = longest_map[buffer.size()];
    words_with_size.push_back(buffer);

    // longest_map is sorted in descending order
    // so the last key is always safe to remove
    if (longest_map.size() > top_size) {
      longest_map.erase(std::prev(longest_map.end()));
    }
  }

  // output
  if (longest_map.empty()) {
    std::cout << "No words without ascenders/descenders." << std::endl;
  } else {
    std::cout << "Longest words without ascenders/descenders (top " << top_size << "):\n";

    for (const auto &pair : longest_map) {
      std::cout << "[" << pair.first << " letters: " << pair.second.size() << " words]:\n";
      for (const auto &word : pair.second) {
        std::cout << word << '\n';
      }
    }

    std::cout << std::endl;
  }

  return EXIT_SUCCESS;
}

// returns true if the word doesn't have uppercase chars, digits
// and ascenders/descenders
// returns false otherwise
bool CheckValid(const std::string &word)
{
  for (char c : word) {
    if (!std::isalpha(c) || std::isupper(c))
      return false;
  }

  return word.find_first_of(asc_and_desc_chars) == std::string::npos;
}
