//
// Created by fynn on 4/9/23.
//

#include <blaze/Forward.h>
#include <blaze/Math.h>

// #include <format> // C++20, for printing style

#include "matrixOperations.h"
#include "linalgTypeDefs.h"

using namespace blaze;

namespace LINALG {

    namespace linearEquationSolvers {

        void solveConjugateGradient(const CompressedMatrix<GLOBAL::scalar, rowMajor> &A,
                                    const DynamicVector<GLOBAL::scalar, columnVector> &b,
                                    DynamicVector<GLOBAL::scalar, columnVector> &x,
                                    const size_t maxIterations,
                                    const double convergenceTolerance);

        void solveGaussSeidel(const CompressedMatrix<GLOBAL::scalar, rowMajor> &A,
                              const std::vector<int> bandIndices,
                              const DynamicVector<GLOBAL::scalar, columnVector> &b,
                              DynamicVector<GLOBAL::scalar, columnVector> &x,
                              const size_t maxIterations,
                              const double convergenceTolerance);
    };
}
