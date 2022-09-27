cmake_minimum_required(VERSION 3.0)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 14)
project(transformations)
cmake_policy(SET CMP0074 NEW)

option(GPU_ACCELERATION "GPU is disabled by Default " OFF)

#include boost and the includes
find_package(Boost REQUIRED)
set(Boost_USE_STATIC_LIBS ON)
include_directories( ${Boost_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include)

IF(GPU_ACCELERATION)
    message("Compiling with CUDA")
    find_package(CUDA REQUIRED)
    set(CUDA_SEPARABLE_COMPILATION ON)

    CUDA_ADD_LIBRARY(alTran 
        ${PROJECT_SOURCE_DIR}/src/matrixexpr.cpp
        ${PROJECT_SOURCE_DIR}/src/altransform.cu
    )
    target_link_libraries(alTran ${CUDA_LIBRARIES})

ELSE()
    set(CUDA_SEPARABLE_COMPILATION OFF)
    message("Compiling with CPU")
    add_library( alTran STATIC
        ${PROJECT_SOURCE_DIR}/src/matrixexpr.cpp
        ${PROJECT_SOURCE_DIR}/src/altransform.cpp
    )

ENDIF()


add_executable(main ${PROJECT_SOURCE_DIR}/src/main.cc)
target_link_libraries(main PUBLIC alTran)


# target_include_directories(main PUBLIC transform)
