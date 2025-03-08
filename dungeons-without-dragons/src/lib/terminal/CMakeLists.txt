add_library(terminal STATIC
        ansiEsc.cpp
        ansiEsc.h
        input.cpp
        input.h)

target_include_directories(terminal PRIVATE .)