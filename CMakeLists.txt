cmake_minimum_required (VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(NutCracker)

SET(SOURCE_FILES
    src/Actions.cpp
    src/BinaryReader.h
    src/BlockState.h
    src/Errors.cpp
    src/Errors.h
    src/Expressions.h
    src/Formatters.h
    src/main.cpp
    src/common.h
    src/NutDecompiler.cpp
    src/NutScript.cpp
    src/NutScript.h
    src/SqObject.cpp
    src/SqObject.h
    src/Statements.cpp
    src/Statements.h)

add_executable(NutCracker ${SOURCE_FILES})
