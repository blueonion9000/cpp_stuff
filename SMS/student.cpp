#include "student.hpp"
#include "nlohmann/json.hpp"

#include <cctype>
#include <ctime>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

// Used when ID is known, e.g. when parsing database
Student::Student(unsigned id, std::string name, std::string surname, std::time_t birth_timestamp,
                 std::string phone_number, SubjectGradeMap grades)
    : id_(id), name_(name), surname_(surname), birth_timestamp_(birth_timestamp), phone_number_(phone_number),
      grades_(grades)
{
}

// Used when adding students at runtime
Student::Student(std::string name, std::string surname, std::time_t birth_timestamp, std::string phone_number,
                 SubjectGradeMap grades = {})
    : name_(name), surname_(surname), birth_timestamp_(birth_timestamp), phone_number_(phone_number), grades_(grades)
{
}

const unsigned &Student::get_id() const
{
  return id_;
}

const std::string &Student::get_name() const
{
  return name_;
}

const std::string &Student::get_surname() const
{
  return surname_;
}

std::string Student::get_full_name() const
{
  return std::string(name_ + ' ' + surname_);
}

int Student::get_age() const
{
  std::time_t current_timestamp = std::time(nullptr);
  return (current_timestamp - birth_timestamp_) / (60 * 60 * 24 * 365);
}

std::string Student::get_birth_date() const
{
  // We temporarily convert std::time_t to std::tm* object, which is easier to work with
  std::tm *birth_tm = std::localtime(&birth_timestamp_);
  std::ostringstream oss;
  oss << birth_tm->tm_mday << '.' << birth_tm->tm_mon + 1 << '.' << birth_tm->tm_year + 1900;
  return oss.str();
}

const std::string &Student::get_phone_number() const
{
  return phone_number_;
}

const Student::SubjectGradeMap &Student::get_grades() const
{
  return grades_;
}

std::vector<std::string> Student::get_classes() const
{
  std::vector<std::string> grades;
  for (const auto &pair : grades_) {
    if (pair.first.empty())
      continue;
    grades.push_back(static_cast<char>(std::toupper(pair.first[0])) + pair.first.substr(1));
  }
  return grades;
}

unsigned Student::get_subject_grade(std::string subject) const
{
  return grades_.find(subject) != grades_.end() ? grades_.at(subject) : 0;
}

nlohmann::json Student::get_json() const
{
  using nlohmann::json;

  json out = json::object({
      {             "id",              id_},
      {           "name",            name_},
      {        "surname",         surname_},
      {"birth_timestamp", birth_timestamp_},
      {   "phone_number",    phone_number_},
      {         "grades",          grades_}
  });

  return out;
}

bool Student::check_legit() const
{
  return !name_.empty() && !surname_.empty() && birth_timestamp_ > 0 && !phone_number_.empty();
}

void Student::set_id(unsigned id)
{
  id_ = id;
}

void Student::set_name(std::string name)
{
  name_ = name;
}

void Student::set_surname(std::string surname)
{
  surname_ = surname;
}

void Student::set_birth_date(std::string date)
{
  // Regex pattern is "XX.XX.XXXX" where X is a digit
  std::string regex_pattern = "^\\d{2}\\.\\d{2}\\.\\d{4}$";
  if (std::regex_match(date, std::regex(regex_pattern))) {
    unsigned day = std::stoul(date.substr(0, date.find_first_of('.')));
    if (day < 1 || day > 31)
      return;

    date = date.substr(date.find_first_of('.') + 1);
    unsigned month = std::stoul(date.substr(0, date.find_first_of('.')));
    if (month < 1 || month > 12)
      return;

    date = date.substr(date.find_first_of('.') + 1);
    unsigned year = std::stoul(date);
    if (year < 1900)
      return;

    std::tm *birth_tm = std::localtime(&birth_timestamp_);

    birth_tm->tm_mday = day;
    birth_tm->tm_mon = month - 1;
    birth_tm->tm_year = year - 1900;

    birth_timestamp_ = std::mktime(birth_tm);
  }
}

void Student::set_phone_number(std::string phone_number)
{
  // Regex pattern is "XXX XXXX XXXX", where X is a digit
  std::string regex_pattern = "^\\d{3}\\ \\d{4}\\ \\d{4}$";
  if (std::regex_match(phone_number, std::regex(regex_pattern))) {
    phone_number_ = phone_number;
  }
}

