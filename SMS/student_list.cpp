#include "student_list.hpp"
#include "student.hpp"

const StudentList::StudentMap &StudentList::get_list() const
{
  return list_;
}

const Student *StudentList::get_student_by_id(Student::id_type id) const
{
  return id_exists(id) ? &list_.at(id) : nullptr;
}

bool StudentList::id_exists(Student::id_type id) const
{
  return list_.find(id) != list_.end();
}

void StudentList::add_student(Student student)
{
  if (id_exists(student.get_id()))
    return;
  list_[student.get_id()] = student;
}

void StudentList::delete_student(Student::id_type id)
{
  if (!id_exists(id))
    return;
  list_.erase(id);
}

Student *StudentList::get_student_by_id_ref(Student::id_type id)
{
  if (id_exists(id))
    return &list_.at(id);
  return nullptr;
}
