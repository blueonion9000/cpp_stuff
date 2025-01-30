#include "func.hpp"

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> EliminateDuplicates(std::vector<std::string> str_vec)
{
  std::sort(str_vec.begin(), str_vec.end());
  auto unique_end_iter = std::unique(str_vec.begin(), str_vec.end());
  str_vec.erase(unique_end_iter, str_vec.end());
  return str_vec;
}

std::vector<std::string> FilterStringByLength(std::vector<std::string> str_vec, char oper, std::string::size_type sz)
{
  if (not(oper == '>' or oper == '<'))
    return str_vec;

  std::stable_sort(str_vec.begin(), str_vec.end(), [oper](const std::string &a, const std::string &b) {
    return oper == '>' ? a.length() > b.length() : a.length() < b.length();
  });

  std::vector<std::string>::iterator end_iter =
      std::find_if_not(str_vec.begin(), str_vec.end(),
                       [oper, sz](const std::string &s) { return oper == '>' ? s.length() > sz : s.length() < sz; });
  str_vec.erase(end_iter, str_vec.end());
  return str_vec;
}

std::string StringVectorToString(const std::vector<std::string> &str_vec, const std::string &separator)
{
  std::ostringstream oss;
  std::for_each(str_vec.begin(), str_vec.end(), [&oss, &separator](const std::string &s) { oss << s << separator; });
  return oss.str();
}
