cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(SortingStacks LANGUAGES CXX)

add_executable(${PROJECT_NAME} src/main.cpp)

add_library(doubly-linked-lists SHARED
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/doubly-linked-lists/base.h
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/doubly-linked-lists/base.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/doubly-linked-lists/number.h
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/doubly-linked-lists/number.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/nodes/doublyNode.h
)

add_library(stack SHARED
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/stack/base.h
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/stack/base.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/stack/number.h
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/stack/number.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/nodes/singleNode.h
)

add_subdirectory(src/lib/terminal)
add_subdirectory(src/lib/algorithm)

target_include_directories(${PROJECT_NAME}
  PRIVATE src/lib/terminal
  PRIVATE src/lib/algorithm
)

# Link Libraries
target_link_libraries(${PROJECT_NAME}
  PRIVATE doubly-linked-lists
  PRIVATE stack
  PRIVATE terminal
  PRIVATE algorithm
)