cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(DungeonsWithoutDragons LANGUAGES CXX)

add_executable(${PROJECT_NAME} src/main.cpp)

add_library(single-linked-lists SHARED
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/single-linked-lists/base.h
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/single-linked-lists/base.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/nodes/singleNode.h
)

add_library(number-single-linked-lists SHARED
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/single-linked-lists/number.h
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/single-linked-lists/number.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/nodes/singleNode.h
)

add_library(queue SHARED
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/queue/base.h
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/queue/base.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/nodes/singleNode.h
)

add_library(undirected-graphs SHARED
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/undirected-graphs/base.h
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/undirected-graphs/base.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/nodes/undirNode.h
  ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/udemy-dsa-cpp/data-structures/edges/weightedEdges.h
)

add_subdirectory(src/lib/dungeons)
add_subdirectory(src/lib/terminal)

# Link Libraries
target_link_libraries(${PROJECT_NAME}
  PRIVATE single-linked-lists
  PRIVATE number-single-linked-lists
  PRIVATE queue
  PRIVATE undirected-graphs
  PRIVATE terminal
)