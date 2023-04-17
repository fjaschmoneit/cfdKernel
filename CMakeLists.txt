cmake_minimum_required(VERSION 3.25)
project(testing)

set(CMAKE_CXX_STANDARD 20)

add_executable(testing main.cpp LINALG/linearEquationSolvers.cpp LINALG/linearEquationSolvers.h LINALG/matrixOperations.cpp LINALG/matrixOperations.h FVM/collocatedField.cpp FVM/collocatedField.h MESH/structured2d.cpp MESH/structured2d.h MESH/baseMesh.h FIELD/dataView.cpp FIELD/dataView.h FIELD/field.cpp FIELD/field.h FIELD/algebra.cpp FIELD/algebra.h)
