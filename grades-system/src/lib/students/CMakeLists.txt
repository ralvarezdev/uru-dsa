add_library(students STATIC
        students.cpp
        students.h)

target_include_directories(students PRIVATE .)