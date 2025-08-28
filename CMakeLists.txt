cmake_minimum_required(VERSION 3.25)
project(gov)

set(CMAKE_CXX_STANDARD 20)

#add_executable(testing main.cpp src/LINALG/linearEquationSolvers.cpp src/LINALG/linearEquationSolvers.h src/LINALG/matrixOperations.cpp src/LINALG/matrixOperations.h src/FVM/collocatedField.cpp src/FVM/collocatedField.h src/MESH/structured2d.cpp src/MESH/structured2d.h src/MESH/baseMesh.h src/FIELD/field.cpp src/FIELD/field.h src/FIELD/algebra.cpp src/FIELD/algebra.h src/globalTypeDefs.h src/LINALG/linalgTypeDefs.h src/FIELD/fieldTypeDefs.h test/matrixOperationsTest.cpp)
include_directories(/usr/local/include)


set(SOURCE_FILES main.cpp)
add_executable(odin_run ${SOURCE_FILES})

include_directories(src)
add_subdirectory(src)

target_link_libraries(odin_run kernel_lib)

#target_link_libraries(DateConverter_run src)
#target_link_libraries(DateConverter_run DateConverter_lib)

add_subdirectory(test)
