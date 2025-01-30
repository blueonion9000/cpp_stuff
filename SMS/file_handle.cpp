#include "file_handle.hpp"
#include "nlohmann/json.hpp"
#include "student.hpp"
#include "student_list.hpp"

#include <fstream>
#include <iostream>

using nlohmann::json;

// Makes a StudentList instance from std::istream
StudentList ParseDatabase(std::istream &is)
{
  json parsed_json = json::parse(is);
  std::vector<json::object_t> student_objs;

  for (auto &student : parsed_json)
    student_objs.push_back(student);

  StudentList::StudentMap student_map;
  for (auto &student : student_objs) {
    Student::SubjectGradeMap grades;
    for (auto &subject_and_grade : student["grades"].items()) {
      grades[subject_and_grade.key()] = subject_and_grade.value();
    }
    Student temp_student(student["id"], student["name"], student["surname"], student["birth_timestamp"],
                         student["phone_number"], grades);
    student_map[temp_student.get_id()] = temp_student;
  }

  return student_map;
}

// Writes database into "./students.json"
// returns false on error
bool SaveDatabase(const StudentList &students)
{
  json out = json::array();
  for (auto &student : students.get_list()) {
    out.push_back(student.second.get_json());
  }

  std::clog << "Opening file for write..." << '\n';
  std::fstream file;
  file.open("students.json", std::fstream::out);
  if (!file)
    return false;

  file << out.dump(2);
  file.close();

  return true;
}
