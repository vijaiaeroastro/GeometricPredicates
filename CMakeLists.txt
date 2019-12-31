cmake_minimum_required(VERSION 3.16)
project(GeomPredicates)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
find_package(Boost REQUIRED)

set(HDRS
        predicates/GenericTypes.hpp
        predicates/point.hpp
        predicates/mesh.hpp)
set(SRCS
        predicates/GenericTypes.cpp
        predicates/point.cpp
        predicates/mesh.cpp)

add_executable(GeomPredicates main.cpp ${HDRS} ${SRCS})