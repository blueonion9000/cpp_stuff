#ifndef STUDENT_HPP
#define STUDENT_HPP

#include "nlohmann/json.hpp"

#include <ctime>
#include <string>
#include <unordered_map>
#include <vector>

class Student {
public:
  using id_type = unsigned;
  using SubjectGradeMap = std::unordered_map<std::string, unsigned>;
  Student() {};
  Student(id_type id, std::string name, std::string surname, std::time_t birth_date, std::string phone_number,
          SubjectGradeMap grades);
  Student(std::string name, std::string surname, std::time_t birth_date, std::string phone_number,
          SubjectGradeMap grades);

  // Get accessors
  const unsigned &get_id() const;
  const std::string &get_name() const;
  const std::string &get_surname() const;
  std::string get_full_name() const;
  int get_age() const;
  std::string get_birth_date() const;
  const std::string &get_phone_number() const;
  const SubjectGradeMap &get_grades() const;
  std::vector<std::string> get_classes() const;
  unsigned get_subject_grade(std::string subject) const;

  // Utility
  nlohmann::json get_json() const;
  bool check_legit() const;

  // Set accessors
  void set_id(unsigned id);
  void set_name(std::string name);
  void set_surname(std::string surname);
  void set_birth_date(std::string date);
  void set_phone_number(std::string phone_number);

private:
  unsigned id_;
  std::string name_;
  std::string surname_;
  std::time_t birth_timestamp_;
  std::string phone_number_;
  SubjectGradeMap grades_;
};

#endif
