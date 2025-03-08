add_library(requests STATIC
        requests.cpp
        requests.h)

target_include_directories(requests PRIVATE .)