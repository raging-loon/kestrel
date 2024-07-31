# CMakeList.txt : CMake project for libdetutil, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("libdetutil" C)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY		  "${CMAKE_SOURCE_DIR}/build")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG  "${CMAKE_SOURCE_DIR}/build")

# Add source to this project's executable.
add_library (libdetutil  
	"include/libdetutil/libdetutil.h"
	"lib/libdetutil.c"
 "include/libdetutil/kdl/kdl.h" "include/libdetutil/string.h" "lib/string.c" )

target_include_directories(libdetutil PUBLIC "./include" "./")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET libdetutil PROPERTY CXX_STANDARD 20)
endif()


# TODO: Add tests and install targets if needed.
