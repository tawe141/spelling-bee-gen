cmake_minimum_required(VERSION 3.10)
project(spelling-bee-gen)

# require python library
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
include_directories("pybind11/include")

# from GoogleTest readme found here: https://github.com/google/googletest/blob/master/googletest/README.md
# downloads GoogleTest, then links the libraries when it compiles

configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif()

add_executable(spelling-bee-gen main.cpp trie.cpp trie.h)

target_link_libraries(spelling-bee-gen ${PYTHON_LIBRARIES})

add_executable(tests tests.cpp trie.h trie.cpp)
#add_compile_options(-fPIC)
target_link_libraries(tests gtest gtest_main ${PYTHON_LIBRARIES})

add_subdirectory(pybind11)
pybind11_add_module(py_spelling_bee_gen trie.h trie.cpp)