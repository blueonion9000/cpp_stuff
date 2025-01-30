#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Date {
public:
  Date(std::string str);
  std::string get();

  size_t get_day()
  {
    return day;
  }

  size_t get_month()
  {
    return month;
  }

  size_t get_year()
  {
    return year;
  }

private:
  size_t month = 0, day = 0, year = 0;
  std::vector<std::string> month_names{"january", "february", "march",     "april",   "may",      "june",
                                       "july",    "august",   "september", "october", "november", "december"};
  std::vector<unsigned> days_in_month = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  bool is_date_valid = true;

  const std::string unsigned_filter = "+1234567890";
  const std::string char_filter = "abcdefghijklmnopqrstuvwxyz";
};

int main(int argc, char **argv)
{
  std::string str;
  std::getline(std::cin, str);
  std::cout << Date(str).get() << std::endl;
  return EXIT_SUCCESS;
}

Date::Date(std::string str)
{
  for (char &ch : str) { // to lower
    ch = std::tolower(ch);
  }

  bool literal_month = false; // month (literal)
  for (std::vector<std::string>::size_type i = 0; i < month_names.size(); ++i) {
    size_t substr_index = str.find(month_names[i].substr(0, 3));
    if (substr_index != std::string::npos) {
      std::string month_str = str.substr(substr_index);
      month_str = std::string(month_str.begin(), month_str.begin() + str.find_first_not_of(this->char_filter));
      if (month_str.compare(month_names[i]) == 0 or month_str.length() == 3) {
        this->month = i + 1;
      } else {
        this->month = 0;
      }
      literal_month = true;
      break;
    }
  }

  if (not literal_month) { // month (numeric)
    str = str.substr(str.find_first_of(this->unsigned_filter));
    size_t month_num = std::stoul(str);
    if (month_num > 12 or month_num < 1) {
      this->month = 0;
    } else {
      this->month = month_num;
    }
    str.erase(str.begin(), str.begin() + str.find_first_not_of(this->unsigned_filter));
  }

  { // day
    str = str.substr(str.find_first_of(this->unsigned_filter));
    size_t day_num = std::stoul(str);
    if (day_num > 31 or day_num < 1) {
      this->day = 0;
    } else {
      this->day = day_num;
    }
    str.erase(str.begin(), str.begin() + str.find_first_not_of(this->unsigned_filter));
  }

  { // year
    str = str.substr(str.find_first_of(this->unsigned_filter));
    this->year = std::stoul(str);
  }

  { // check if valid
    bool leap_year = false;
    if (year % 400 == 0 or (year % 4 == 0 and year % 100 != 0)) {
      leap_year = true;
    }

    if (!(month and day) || (!leap_year && month == 2 && day > 28) || (day > days_in_month[month - 1])) {
      is_date_valid = false;
      return;
    }
  }
}

inline std::string Date::get()
{
  std::ostringstream date;
  if (is_date_valid) {
    date << static_cast<char>(std::toupper(month_names[month - 1][0])) << month_names[month - 1].substr(1) << " " << day
         << ", " << year;
  } else {
    date << "null";
  }
  return date.str();
}
