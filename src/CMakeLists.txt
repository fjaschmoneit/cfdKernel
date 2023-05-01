project(kernel)

set(HEADER_FILES
        FIELD/field.h
        FIELD/algebra.h
        FIELD/fieldTypeDefs.h
        FVM/collocatedField.h
        FVM/coefficientMatrixGenerator.h
        LINALG/linalgTypeDefs.h
        LINALG/linearEquationSolvers.h
        LINALG/matrixOperations.h
        MESH/baseMesh.h
        MESH/structured2d.h
        globalTypeDefs.h
        )

set(SOURCE_FILES
        FIELD/field.cpp
        FIELD/algebra.cpp
        FVM/collocatedField.cpp
        FVM/coefficientMatrixGenerator.cpp
        LINALG/linearEquationSolvers.cpp
        LINALG/matrixOperations.cpp
        MESH/structured2d.cpp)

add_library(kernel_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})