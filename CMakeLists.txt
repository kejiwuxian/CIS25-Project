cmake_minimum_required (VERSION 3.21)
project(Unit-Price-Calculator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
if(MSVC)
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif(MSVC)

add_subdirectory (extern/googletest)

include_directories(include ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

file(GLOB SOURCES "src/*.cpp")
add_executable(main_exec "main.cpp" ${SOURCES})
add_executable(test_exec "test/test.cpp" ${SOURCES})

target_link_libraries(test_exec gtest gtest_main)

enable_testing()
add_test (NAME Unit-Price-Calculator COMMAND test_exec)