//
// Created by fynn on 4/9/23.
//

#include <blaze/Forward.h>
#include <blaze/Math.h>

#include "linalgTypeDefs.h"

using namespace blaze;

namespace LINALG {

    namespace linearEquationSolvers {

        void solveConjugateGradient(const CompressedMatrix<GLOBAL::scalar, rowMajor> &A,
                                    const DynamicVector<GLOBAL::scalar, columnVector> &b,
                                    DynamicVector<GLOBAL::scalar, columnVector> &x,
                                    const size_t iterations,
                                    const double convergenceLimit);
    };
}
