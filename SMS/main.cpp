#include "file_handle.hpp"
#include "student.hpp"
#include "student_list.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

unsigned char GetUserMenuInput();
std::string GetLine();

int main(int argc, char **argv)
{
  // Handle args
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " FILE" << std::endl;
    return EXIT_FAILURE;
  }

  // Handle file
  std::ifstream file(argv[1], std::fstream::in);
  if (!file) {
    std::cerr << "Error: invalid file." << std::endl;
    return EXIT_FAILURE;
  }

  // Parse database
  std::clog << "Parsing database " << argv[1] << "...\n";
  StudentList students_list(ParseDatabase(file));
  std::clog << "Database parsed." << '\n';
  std::cout << '\n';

  bool is_work_done = false;
  bool is_pending_changes = false;

  // Menu logic
  // Crudest solution possible
  while (!is_work_done) {
    std::cout << "[Student Management System]" << '\n'
              << "1. Add new student" << '\n'
              << "2. View all students" << '\n'
              << "3. Get student info" << '\n'
              << "4. Edit student details" << '\n'
              << "5. Delete student" << '\n'
              << "w. Write database" << '\n'
              << "e. Exit" << '\n'
              << '\n';

    std::cout << "Enter your choice: ";
    unsigned user_choice = GetUserMenuInput();
    std::cout << '\n';

    switch (user_choice) {
    case ('1'): {
      Student temp_student;

      GetLine(); // Idk why but without this I don't get to enter name
      std::cout << "Enter name: ";
      temp_student.set_name(GetLine());
      std::cout << "Enter surname: ";
      temp_student.set_surname(GetLine());
      std::cout << "Enter date of birth (dd.mm.yyyy): ";
      temp_student.set_birth_date(GetLine());
      std::cout << "Enter phone number (XXX XXXX XXXX): ";
      temp_student.set_phone_number(GetLine());

      if (temp_student.check_legit()) {
        temp_student.set_id((students_list.get_list().rbegin()->first) + 1);
        students_list.add_student(temp_student);
        std::cout << "Student with ID " << temp_student.get_id() << " added." << '\n';
        is_pending_changes = true;
      } else {
        std::cout << "Cannot add student: one or more fields are invalid." << '\n';
      }
    } break;
    case ('2'):
      if (students_list.get_list().empty()) {
        std::clog << "Nothing to list: student database is empty." << '\n';
        break;
      }

      std::cout << "[List of all students]" << '\n';
      for (const auto &pair : students_list.get_list()) {
        const auto &student = pair.second;
        std::cout << "ID " << student.get_id() << ": " << student.get_full_name() << " (" << student.get_age() << ")"
                  << '\n';
      }
      break;
    case ('3'):
      std::cout << "Enter student ID: ";
      {
        Student::id_type id = 0;
        std::cin >> id;
        if (students_list.id_exists(id)) {
          const auto &student = students_list.get_student_by_id(id);
          std::cout << "[Student ID " << id << " info]" << '\n'
                    << "Full name: " << student->get_full_name() << '\n'
                    << "Date of birth: " << student->get_birth_date() << '\n'
                    << "Phone number: " << student->get_phone_number() << '\n';
          std::cout << "Grades: " << '\n';
          if (!student->get_grades().empty()) {
            for (const auto &subject_and_grade : student->get_grades()) {
              std::cout << '\t' << subject_and_grade.first << ": " << subject_and_grade.second << '\n';
            }
          } else {
            std::cout << '\t' << "No grades info." << '\n';
          }
        } else {
          std::cout << "Cannot get info for student with ID " << id << ": no such student." << '\n';
        }
      }
      break;
    case ('4'): {
      std::cout << "Enter student ID: ";
      unsigned id;
      std::cin >> id;
      if (!students_list.id_exists(id)) {
        std::cout << "Cannot edit details for student with ID " << id << ": no such student." << '\n';
        break;
      }

      Student *target_student = students_list.get_student_by_id_ref(id);
      Student temp_student;

      GetLine();
      std::cout << "Enter name (" << target_student->get_name() << "): ";
      temp_student.set_name(GetLine());
      std::cout << "Enter surname (" << target_student->get_surname() << "): ";
      temp_student.set_surname(GetLine());
      std::cout << "Enter date of birth (" << target_student->get_birth_date() << "): ";
      temp_student.set_birth_date(GetLine());
      std::cout << "Enter phone number (" << target_student->get_phone_number() << "): ";
      temp_student.set_phone_number(GetLine());

      if (temp_student.check_legit()) {
        *target_student = temp_student;
        std::cout << "Editing student with ID " << target_student->get_id() << ": success." << '\n';
      } else {
        std::cout << "Cannot edit student with ID " << target_student->get_id() << ": one or more fields are invalid."
                  << '\n';
      }

      is_pending_changes = true;
    } break;
    case ('5'): {
      std::cout << "Enter student ID: ";
      Student::id_type id = 0;
      std::cin >> id;
      if (!students_list.id_exists(id)) {
        std::cout << "Cannot delete student with ID " << id << ": no such student." << '\n';
        break;
      }
      students_list.delete_student(id);
      std::cout << "Successfully deleted student with ID " << id << '\n';
    } break;
    case ('w'): {
      std::clog << "Saving database..." << '\n';
      bool successful_write = SaveDatabase(students_list);
      if (successful_write) {
        is_pending_changes = false;
        std::clog << "Database saved successfully.";
      } else {
        std::cerr << "Database write error.";
      }
    } break;
    case ('e'):
      if (is_pending_changes) {
        std::cout << "There are unsaved changes, do you really want to exit? (type 'y'): ";
        unsigned char input;
        std::cin >> input;
        if (input == 'y') {
          is_work_done = true;
        }
      }
      break;
    }
    std::cout << '\n';
    std::flush(std::cout);
  }

  return EXIT_SUCCESS;
}

unsigned char GetUserMenuInput()
{
  unsigned char user_input = '\0';
  std::string options = "123456we";
  while (true) {
    std::cin >> user_input;
    if (std::string(1, user_input).find_first_of(options) != std::string::npos) {
      return user_input;
    }
    std::cerr << "Wrong input \'" << user_input << "\'. Try again: ";
  }
}

std::string GetLine()
{
  std::string temp;
  std::getline(std::cin, temp);
  return temp;
};
