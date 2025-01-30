#ifndef FUNC_HPP_
#define FUNC_HPP_

#include <string>
#include <vector>

std::vector<std::string> EliminateDuplicates(std::vector<std::string>);
std::vector<std::string> FilterStringByLength(std::vector<std::string>, char, std::string::size_type);
std::string StringVectorToString(const std::vector<std::string> &, const std::string &);

#endif
