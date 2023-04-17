//
// Created by fynn on 4/10/23.
//

#ifndef TESTING_MATRIXOPERATIONS_H
#define TESTING_MATRIXOPERATIONS_H

#include <blaze/Math.h>
#include <algorithm>

using namespace blaze;

namespace LINALG {

    namespace matrixOperations {

        CompressedMatrix<double, rowMajor> newIdentityMatrix(const size_t NN);

        void fillBand(const long bandID,
                      CompressedMatrix<double, rowMajor> &A,
                      const DynamicVector<double, columnVector> &bandAr);


    };

}


#endif //TESTING_MATRIXOPERATIONS_H
