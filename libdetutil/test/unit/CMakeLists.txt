cmake_minimum_required(VERSION 3.14)
project(ldu_unit_test)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  ldu_unit_test
  test_main.cpp
)
target_link_libraries(
  ldu_unit_test
  GTest::gtest_main
  "${CMAKE_SOURCE_DIR}/../../build/libdetutil.lib"
)

target_include_directories(
	ldu_unit_test
	PUBLIC
	"${CMAKE_SOURCE_DIR}/../../include"
)

include(GoogleTest)
gtest_discover_tests(ldu_unit_test)
