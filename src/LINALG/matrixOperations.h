//
// Created by fynn on 4/10/23.
//


#include <blaze/Math.h>
#include <algorithm>

#include "linalgTypeDefs.h"


using namespace blaze;

namespace LINALG {

    namespace matrixOperations {

        CompressedMatrix<GLOBAL::scalar, rowMajor> newIdentityMatrix(const size_t NN);
        CompressedMatrix<GLOBAL::scalar, rowMajor> newZeroMatrix(const size_t NN);

        void fillBand(const long bandID,
                      CompressedMatrix<GLOBAL::scalar, rowMajor> &A,
                      const DynamicVector<GLOBAL::scalar, columnVector> &bandAr);


    };

}

