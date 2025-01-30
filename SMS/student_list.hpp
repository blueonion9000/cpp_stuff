#ifndef STUDENT_LIST_HPP
#define STUDENT_LIST_HPP

#include "student.hpp"
#include <map>

class StudentList {
public:
  using StudentMap = std::map<Student::id_type, Student>;
  StudentList(const StudentMap &list) : list_(list) {};

  const StudentMap &get_list() const;
  const Student *get_student_by_id(Student::id_type id) const;
  bool id_exists(Student::id_type id) const;

  void add_student(Student student);
  void delete_student(Student::id_type id);
  Student *get_student_by_id_ref(Student::id_type id);

private:
  StudentMap list_;
};

#endif
