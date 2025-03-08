cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(CollegeTest2 LANGUAGES CXX)

add_executable(${PROJECT_NAME} src/main.cpp)

add_library(stack SHARED
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/stack/base.h
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/stack/base.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/stack/number.h
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/stack/number.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/nodes/singleNode.h
)

add_library(queue SHARED
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/queue/base.h
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/queue/base.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/nodes/singleNode.h
)

add_subdirectory(src/lib/emergency)

# Link Libraries
target_link_libraries(${PROJECT_NAME}
  PRIVATE stack
  PRIVATE queue
  PRIVATE emergency
)