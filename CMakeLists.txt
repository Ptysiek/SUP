cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#___________________________________________________________________________
# set the project name
project(sup)

#___________________________________________________________________________
# set executables
set(THIS_PROJECT_SRC_DIRECTORIES
    source/tools/IgnoreFiles.cpp
)
#set(THIS_PROJECT_TESTS_DIRECTORIES
#)

#___________________________________________________________________________
# set flags
set(THIS_PROJECT_FLAGS
    -Wall
    -Werror 
    -Weffc++
    -Wextra
    -pedantic
    -Wconversion 
    -O3
)

#___________________________________________________________________________
# add all executables
add_executable(${PROJECT_NAME}
    source/main.cpp
    ${THIS_PROJECT_SRC_DIRECTORIES}
)
#add_executable(${PROJECT_NAME}-ut 
#    source/catch_main.cpp
#    ${THIS_PROJECT_SRC_DIRECTORIES}
#    ${THIS_PROJECT_TESTS_DIRECTORIES}
#)
    
#___________________________________________________________________________
# specify compile options for target
target_compile_options(${PROJECT_NAME} PRIVATE ${THIS_PROJECT_FLAGS})

#___________________________________________________________________________
# enable standard cpp17
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

#___________________________________________________________________________
# link ncurses static lib
target_link_libraries(${PROJECT_NAME} ncurses)

#___________________________________________________________________________
# { ctest, ctest -V }
#enable_testing()
#add_test(NAME ${PROJECT_NAME}-ut COMMAND ${PROJECT_NAME}-ut)
