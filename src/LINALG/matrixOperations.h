//
// Created by fynn on 4/10/23.
//


#include <blaze/Math.h>
#include <algorithm>

#include "linalgTypeDefs.h"

#include <iostream>


using namespace blaze;

namespace LINALG {

    namespace matrixOperations {

        CompressedMatrix<GLOBAL::scalar, rowMajor> newIdentityMatrix(const size_t NN);
        CompressedMatrix<GLOBAL::scalar, rowMajor> newZeroMatrix(const size_t NN);

        void copyBandElements(
            Band<const CompressedMatrix<GLOBAL::scalar>,false,false,false> srcBand,
            Band<CompressedMatrix<GLOBAL::scalar>,false,false,false> trgBand);

        // vector of lower off diagonals contains the non-positive indices of lower matrix bands.
        matrix invertLowerTriangularBandMatrix(
            const matrix &A);

        // Off-diagonal bands have fewer elements than number of columns in A.
        // If bandAr contains more elements than fit onto the off-diagonal, the last ones are disregarded.
        // void fillBand(const long bandIndex,
        //               CompressedMatrix<GLOBAL::scalar, rowMajor> &A,
        //               const DynamicVector<GLOBAL::scalar, columnVector> &bandAr);

        // positive bandIndex Q point to first band element in first row in column Q
        // negative bandIndex Q point to first band element in first column in row Q
        // vector getBandEntries(const int bandIndex,
        //                       const CompressedMatrix<GLOBAL::scalar, rowMajor> &A );

        void getUpperTriangularBandIndices(const CompressedMatrix<GLOBAL::scalar, rowMajor> &A, std::vector<int> &indices);

        void lu(const CompressedMatrix<GLOBAL::scalar, rowMajor> &A,
                CompressedMatrix<GLOBAL::scalar, rowMajor> &lower,
                CompressedMatrix<GLOBAL::scalar, rowMajor> &upper,
                CompressedMatrix<GLOBAL::scalar, rowMajor> &diagonal);

    };

}

