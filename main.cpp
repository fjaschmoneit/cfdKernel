#include <iostream>
#include <blaze/Forward.h>
#include <blaze/Math.h>

#include "globalTypeDefs.h"
#include "FVM/linEqSystem.h"
#include "LINALG/linearEquationSolvers.h"
#include "MESH/structured2d.h"
#include "FIELD/field.h"

int main()
{

    auto mesh(MESH::structured2dRegularRectangle( 0.1, 0.1, 50 ));
    auto T = FIELD::field( mesh );

    const size_t NN(mesh.nbCells);







    // defining fluxes
    GLOBAL::vector ap{3,2,2,2,3};
    GLOBAL::vector ae(5,-1);
    GLOBAL::vector aw(5,-1);
    GLOBAL::vector sourceTerms{2*100,0,0,0,2*500};

    // translating fluxes to coefficient arrays
    FVM::linEqSystem coeffGen { mesh };
    coeffGen.setDirectionalFlux( ap, FVM::CardinalDirection::centre );
    coeffGen.setDirectionalFlux( ae, FVM::CardinalDirection::east );
    coeffGen.setDirectionalFlux( aw, FVM::CardinalDirection::west );
    coeffGen.setConstVec( sourceTerms );

    // linear system templates
    LINALG::matrix A = LINALG::matrixOperations::newIdentityMatrix(NN);
    LINALG::vector b = LINALG::vector(NN, 0.0);
    LINALG::vector x = LINALG::vector(NN, 0.0);

    // // coeffGen brings fluxes and linear system together
    // coeffGen.assembleCoeffMatrix(A);
    // coeffGen.assembleConstVec( b );
    //
    // solve system
    LINALG::linearEquationSolvers::solveConjugateGradient(A, b, x, 1e2, 1e-5);
    std::cout<< A << std::endl;
    std::cout << x << std::endl;

    return 0;
}

