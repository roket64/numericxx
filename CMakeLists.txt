cmake_minimum_required(VERSION 3.11.0)

enable_testing()
add_subdirectory(test)

project(numericxx
        VERSION 0.1.0
        LANGUAGES C CXX
)

function(add_headers VAR)
  set(headers ${${VAR}})
  foreach(header ${ARGN})
    set(headers ${headers} include/numericxx/${header})
  endforeach(header ${ARGN})
endfunction()

set(NUMERICXX_VERSION_MAJOR 0)
set(NUMERICXX_VERSION_MINOR 1)
set(NUMERICXX_VERSION_PATCH 0)

set(NUMERICXX_PC_IN ${PROJECT_SOURCE_DIR}/pkg/numericxx.pc.in)

set(NUMERICXX_INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR})

set(NUMERICXX_INSTALL_INCDIR ${CMAKE_INSTALL_INCLUDEDIR}/numericxx)

set(NUMERICXX_HEADERS)

add_headers(NUMERICXX_HEADERS
  # algorithm.hpp
  # arithmetic.hpp
  # cipher.hpp
  config.hpp
  # congruence.hpp
  # exception.hpp
  # gaussian_int.hpp
  # prime.hpp
  # sieve.hpp
  types.hpp
  version.hpp
)

set(NUMERICXX_SOURCES
  # src/algorithm.cpp
  # src/arithmetic.cpp
  # src/cipher.cpp
  src/config.cpp
  # src/congruence.cpp
  # src/exception.cpp
  # src/gaussian_int.cpp
  # src/prime.cpp
  # src/sieve.cpp
  src/types.cpp
  src/version.cpp
)

add_library(numericxx SHARED 
  ${NUMERICXX_SOURCES}
  # ${NUMERICXX_HEADERS}
)

set_target_properties(numericxx 
  PROPERTIES 
  VERSION ${NUMERICXX_VERSION_MAJOR}.${NUMERICXX_VERSION_MINOR}.${NUMERICXX_VERSION_PATCH}
  SOVERSION ${NUMERICXX_VERSION_MAJOR}
  PUBLIC_HEADER "${NUMERICXX_HEADERS}"
)

target_include_directories(numericxx PRIVATE include)

configure_file(
  ${NUMERICXX_PC_IN}
  ${PROJECT_SOURCE_DIR}/pkg/numericxx.pc
  @ONLY
)

include(GNUInstallDirs)

# install the library and headers
install(TARGETS ${INSTALL_TARGETS}
  LIBRARY DESTINATION ${NUMERICXX_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${NUMERICXX_INSTALL_INCDIR}
)

# install package configs
install(FILES ${NUMERICXX_PC_IN}
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)
