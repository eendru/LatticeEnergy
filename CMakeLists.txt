project(LatticeEnergy)
cmake_minimum_required(VERSION 3.6)

#libyaml-cpp
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(FindLIBYAML_CPP)
find_package(LIBYAML_CPP REQUIRED)

#GNU Science Library
find_package(GSL REQUIRED)

set(CMAKE_CXX_STANDARD 11)

add_executable(LatticeEnergy
                    Lattice.cc
                    Energy.cc)

target_link_libraries(LatticeEnergy GSL::gsl GSL::gslcblas yaml-cpp)

configure_file(config.yaml config.yaml COPYONLY)

