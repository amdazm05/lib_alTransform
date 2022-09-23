cmake_minimum_required(VERSION 3.0)
project(transformations)

set(BOOST_INCLUDE_DIR "C:/boost/include/boost-1_79")
set(BOOST_SRC_DIR "C:/boost/lib/")




message(STATUS  "Alleged boost lib path ${BOOST_SRC_DIR}")
message(STATUS  "Alleged boost include path ${BOOST_INCLUDE_DIR}")

add_executable(main ${PROJECT_SOURCE_DIR}/src/main.cc)
target_include_directories(main PUBLIC  ${PROJECT_SOURCE_DIR}/include ${BOOST_INCLUDE_DIR})
target_include_directories(main PUBLIC transform)
# target_link_libraries(main PUBLIC ${BOOST_SRC_DIR})