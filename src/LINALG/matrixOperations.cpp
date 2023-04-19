//
// Created by fynn on 4/10/23.
//


#include "matrixOperations.h"

using namespace LINALG;

CompressedMatrix<GLOBAL::scalar,rowMajor> matrixOperations::newZeroMatrix(const size_t NN){
    return { NN, NN };
}


CompressedMatrix<GLOBAL::scalar,rowMajor> matrixOperations::newIdentityMatrix(const size_t NN){

    CompressedMatrix<GLOBAL::scalar,rowMajor> A( NN, NN );
    A.reserve( NN );
    vector ones(NN,1.0);
    matrixOperations::fillBand(0, A, ones);

    return A;
}

void matrixOperations::fillBand(const long bandID,
                                CompressedMatrix<GLOBAL::scalar, rowMajor> &A,
                                const DynamicVector<GLOBAL::scalar, columnVector> &bandAr) {

    const size_t NN = bandAr.size();

    for (size_t r = 0; r < NN; ++r) {
        const long c = r+bandID;

        if ( c >= 0 ){
            A(r,c) = bandAr[r];
        }
    }
}