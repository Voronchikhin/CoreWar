cmake_minimum_required(VERSION 3.5.1)
project(coreWAR)

set (CMAKE_CXX_STANDARD 11)



include_directories("include")


set(SOURCE_FILES  src/main.cpp
        src/core.cpp 
        include/core.hpp
        include/executionContext.hpp
        include/instruction.hpp
        src/instruction.cpp
        src/executionContext.cpp
        src/movInstruction.cpp
        src/arithmeticInstr.cpp
        src/datComand.cpp
        src/jumpComand.cpp
        src/splCommand.cpp
        src/boolComand.cpp
        src/parser.cpp
        include/parser.hpp
        include/mars.hpp
        src/mars.cpp
)
add_executable(coreWAR ${SOURCE_FILES})
