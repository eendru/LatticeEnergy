project(LatticeEnergy)
cmake_minimum_required(VERSION 3.6)

set (CMAKE_CXX_STANDARD 11)

add_executable(LatticeEnergy
                    Lattice.cc
                    Energy.cc)

find_package(GSL REQUIRED)
target_link_libraries(LatticeEnergy GSL::gsl GSL::gslcblas)

