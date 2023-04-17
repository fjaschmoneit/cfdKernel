//
// Created by fynn on 4/9/23.
//

#include "linearEquationSolvers.h"
#include <iostream>


using namespace LINALG;

void linearEquationSolvers::solveConjugateGradient(const CompressedMatrix<double, rowMajor> &A,
                                                   const DynamicVector<double, columnVector> &b,
                                                   DynamicVector<double, columnVector> &x,
                                                   const size_t iterations,
                                                   const double convergenceLimit) {

    const size_t NN = b.size();
    DynamicVector<double,columnVector> r( NN ), p( NN ), Ap( NN );
    double alpha, beta, delta;

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
            // debug message:
            std::cout << "conjugate gradient converged after "<< iteration <<  "iterations." << std::endl;
            break;
        }
        p = r + ( beta / delta ) * p;
        delta = beta;
    }
}
