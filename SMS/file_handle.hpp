#ifndef FILE_HANDLE_HPP
#define FILE_HANDLE_HPP

#include "student_list.hpp"

#include <istream>

StudentList ParseDatabase(std::istream &ifs);
bool SaveDatabase(const StudentList &);

#endif
