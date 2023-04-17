//
// Created by fynn on 4/9/23.
//

#ifndef TESTING_LINEAREQUATIONSOLVERS_H
#define TESTING_LINEAREQUATIONSOLVERS_H

#include <blaze/Forward.h>
#include <blaze/Math.h>


using namespace blaze;

namespace LINALG {

    namespace linearEquationSolvers {

        void solveConjugateGradient(const CompressedMatrix<double, rowMajor> &A,
                                    const DynamicVector<double, columnVector> &b,
                                    DynamicVector<double, columnVector> &x,
                                    const size_t iterations,
                                    const double convergenceLimit);


    };

}

#endif //TESTING_LINEAREQUATIONSOLVERS_H
