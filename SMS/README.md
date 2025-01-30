# Student Management System (SMS)

This little program tries to mimic some sort of student management software.
It parses a database stored in a `json` file and allows you to do several things listed below:
```
[Student Management System]
1. Add new student
2. View all students
3. Get student info
4. Edit student details
5. Delete student
w. Write database
e. Exit
```

"Noteable" code features:
1. Header files
2. Parsing and saving JSON using 3rd party library ([nlohmann/json](https://github.com/nlohmann/json))
3. Handling of command line arguments
4. File I/O (`std::fstream`)
5. Classes
6. Pointers and references
7. Function (constructor) overloading
8. `std::map` for holding `Student` instances
9. Working with dates and time using `<ctime>` library
10. Basic `<regex>` library utilisation

### Building

```
clang++ -std=c++11 -o SMS main.cpp file_handle.cpp student.cpp student_list.cpp
```

### Usage

```
./SMS FILE
```
Where `FILE` is a valid `json` file.