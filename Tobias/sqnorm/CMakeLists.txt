cmake_minimum_required(VERSION 3.10)

project(sqnorm)
add_executable(sqnorm test.cpp)

set_property(TARGET sqnorm PROPERTY CXX_STANDARD 20)
set_property(TARGET sqnorm PROPERTY COMPILE_WARNING_AS_ERROR)


target_compile_options(sqnorm PUBLIC "-pedantic") #
target_compile_options(sqnorm PUBLIC "-ffast-math") #
target_compile_options(sqnorm PUBLIC "-march=native") #

target_link_libraries(sqnorm tbb)



set_property(TARGET sqnorm PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)

