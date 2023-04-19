#include <iostream>
#include <blaze/Forward.h>
#include <blaze/Math.h>

#include "globalTypeDefs.h"

#include "LINALG/linearEquationSolvers.h"
#include "LINALG/matrixOperations.h"
#include "LINALG/linalgTypeDefs.h"

#include "MESH/structured2d.h"
#include "FIELD/field.h"


int main()
{

    auto mesh(MESH::structured2dRegularRectangle( 5.0, 1.0, 1 ));
    auto T = FIELD::field( mesh );

    const size_t NN(mesh.nbCells);
    LINALG::matrix A = LINALG::matrixOperations::newIdentityMatrix(NN);
    std::cout << A << std::endl;

//building matrix:
    LINALG::vector ap{3,2,2,2,3};
    LINALG::vector ae(5,-1);
    LINALG::vector aw(5,-1);

    LINALG::matrixOperations::fillBand(0, A, ap); // central band
    LINALG::matrixOperations::fillBand(1, A, ae); // east band
    LINALG::matrixOperations::fillBand(-1, A, aw); // west band

    // building source vector:
    LINALG::vector b{2*100,0,0,0,2*500};

    std::cout<< A << std::endl;
    blaze::DynamicVector<GLOBAL::scalar,blaze::columnVector> x( NN, 0.1 );// b( NN, 1.0 );
    LINALG::linearEquationSolvers::solveConjugateGradient(A, b, x, 1e2, 1e-5);
    std::cout << x << std::endl;

    return 0;
}

