//
// Created by fynn on 4/9/23.
//

#include "linearEquationSolvers.h"
#include <iostream>


using namespace LINALG;

void linearEquationSolvers::solveGaussSeidel(const CompressedMatrix<GLOBAL::scalar, rowMajor> &A,
                                             const std::vector<int> bandIndices,
                                             const DynamicVector<GLOBAL::scalar, columnVector> &b,
                                             DynamicVector<GLOBAL::scalar, columnVector> &x,
                                             const size_t maxIterations,
                                             const double convergenceTolerance) {

    const size_t n = A.rows();
    CompressedMatrix<GLOBAL::scalar, rowMajor> L(n,n), U(n,n), D(n,n);

    std::for_each(bandIndices.begin(), bandIndices.end(),
        [&](const int bi) {
            if (bi > 0) {
                matrixOperations::copyBandElements( band(A,bi), band(U,bi) );
            } else if (bi < 0) {
                matrixOperations::copyBandElements( band(A,bi), band(L,bi) );
            } else {
                matrixOperations::copyBandElements( band(A,bi), band(D,bi) );
            }
        } );

    const matrix N = matrixOperations::invertLowerTriangularBandMatrix( D+L );

    size_t counter = 0;
    vector x_old(x+2);

    auto residualNorm = linfNorm(b-A*x );
    auto variableChange = linfNorm(x_old- x);
    while (residualNorm > convergenceTolerance && variableChange != 0. && counter < maxIterations ) {
        x_old = x;
        x = -N*U*x_old + N*b;
        residualNorm = linfNorm(b-A*x );
        variableChange = linfNorm(x_old- x);
        // std::cout<< "residual norm = " << residualNorm << "\t variable max diff = " << variableChange << std::endl;
        counter++;
    }

    if ( counter == maxIterations || variableChange == 0. ) {
        // throw std::runtime_error(std::format(
        //     "Gauss-Seidel failed to converge: residual norm = {:.6e}, tolerance = {:.6e}, iterations = {}",
        //     residualNorm, convergenceTolerance, maxIterations));

        throw std::runtime_error("Gauss-Seidel failed to converge: residual norm = " + std::to_string(residualNorm)
                                 + ", tolerance = " + std::to_string(convergenceTolerance)
                                 + ", variable diff = " + std::to_string(variableChange)
                                 + ", iterations = " + std::to_string(counter));
    }
    std::cout<< "Gauss-Seidel converged with residual = " << residualNorm << ", in " << counter << " iterations." << std::endl;
}


// A must be symmetric and positive definite
void linearEquationSolvers::solveConjugateGradient(const CompressedMatrix<GLOBAL::scalar, rowMajor> &A,
                                                   const DynamicVector<GLOBAL::scalar, columnVector> &b,
                                                   DynamicVector<GLOBAL::scalar, columnVector> &x,
                                                   const size_t iterations,
                                                   const double convergenceLimit) {

    if( !isSymmetric( A ) ) {
        throw std::runtime_error("Conjugate gradient not applicable: A is not symmetric.");
    }

    const size_t NN = b.size();
    DynamicVector<GLOBAL::scalar ,columnVector> r( NN ), p( NN ), Ap( NN );
    GLOBAL::scalar alpha, beta, delta;

    r = b - A * x;
    p = r;
    delta = (r,r);

    for( size_t iteration=0UL; iteration<iterations; ++iteration )
    {
        Ap = A * p;
        alpha = delta / (p,Ap);
        x += alpha * p;
        r -= alpha * Ap;

        beta = (r,r);
        if( std::sqrt( beta/delta ) < convergenceLimit ) {
            break;
        }
        p = r + ( beta / delta ) * p;
        delta = beta;
    }
}