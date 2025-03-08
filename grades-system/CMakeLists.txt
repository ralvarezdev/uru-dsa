cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(GradesSystem LANGUAGES CXX)

add_executable(${PROJECT_NAME} src/main.cpp)

add_library(single-linked-lists SHARED
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/single-linked-lists/base.h
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/single-linked-lists/base.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/nodes/singleNode.h
)

add_subdirectory(src/lib/students)
add_subdirectory(src/lib/terminal)

target_include_directories(${PROJECT_NAME}
  PRIVATE src/lib/students
  PRIVATE src/lib/terminal
)

# Link Libraries
target_link_libraries(${PROJECT_NAME}
  PRIVATE terminal
  PRIVATE students
  PRIVATE single-linked-lists
)