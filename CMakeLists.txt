cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 14)
project(transformations)
cmake_policy(SET CMP0074 NEW)

add_library(
    alTran
    STATIC
    ${PROJECT_SOURCE_DIR}/src/altransform.cpp
    ${PROJECT_SOURCE_DIR}/src/matrixexpr.cpp
)

find_package(Boost REQUIRED)
set(Boost_USE_STATIC_LIBS ON)

target_include_directories(
    alTran
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
)


add_executable(main ${PROJECT_SOURCE_DIR}/src/main.cc)
target_link_libraries(main PUBLIC alTran)


# target_include_directories(main PUBLIC transform)
