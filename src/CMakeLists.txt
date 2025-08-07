project(kernel)

set(HEADER_FILES
        FIELD/field.h
        FIELD/algebra.h
        FIELD/obsolete_fieldTypeDefs.h
        FVM/collocatedField.h
        FVM/linEqSystem.h
        LINALG/linalgTypeDefs.h
        LINALG/linearEquationSolvers.h
        LINALG/matrixOperations.h
        MESH/baseMesh.h
        MESH/structured2d.h
        globalTypeDefs.h
        SOLVER/scalarTransport.h
        )

set(SOURCE_FILES
        FIELD/algebra.cpp
        FVM/collocatedField.cpp
        FVM/linEqSystem.cpp
        LINALG/linearEquationSolvers.cpp
        LINALG/matrixOperations.cpp
        MESH/structured2d.cpp
        SOLVER/scalarTransport.cpp
        FIELD/fieldProxy.h
)

add_library(kernel_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

# Points to src/
target_include_directories(kernel_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})