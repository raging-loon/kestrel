cmake_minimum_required(VERSION 3.10)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/")

option(ENABLE_TESTS "Enable Unit Testing" OFF)

project("kestrel")

add_subdirectory(libkds)
add_subdirectory(sensor)


if(ENABLE_TESTS)
    add_subdirectory(tests)
endif()

