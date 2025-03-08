add_library(terminal STATIC
        ansiEsc.cpp
        ansiEsc.h
        input.cpp
        input.h
        cols.cpp
        cols.h)

target_include_directories(terminal PRIVATE .)