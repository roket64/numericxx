cmake_minimum_required(VERSION 3.11.0)

enable_testing()
add_subdirectory(tests)

project(numericxx
        VERSION 0.1.0
        LANGUAGES C CXX
)

file(GLOB_RECURSE
    PROJECT_SOURCES
    RELATIVE
    ${CMAKE_SOURCE_DIR}
    "src/*.cpp"
)

set(GCC_COMPILE_OPTIONS
    -Wall -Wextra -Werror -pedantic -std=c++20
)

set(GCC_COMPILE_OPTIONS_DEBUG
  ${GCC_COMPILE_OPTIONS} -g -O0
)

set(GCC_COMPILE_OPTIONS_RELEASE
  ${GCC_COMPILE_OPTIONS} -O3
)

include_directories(include)

add_library(numericxx STATIC src/main.cpp)

install(TARGETS numericxx DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
