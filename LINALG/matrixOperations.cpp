//
// Created by fynn on 4/10/23.
//


#include "matrixOperations.h"

using namespace LINALG;

CompressedMatrix<double,rowMajor> matrixOperations::newIdentityMatrix(const size_t NN){

    CompressedMatrix<double,rowMajor> A( NN, NN );

    A.reserve( NN );                // Allocate the total amount of memory
//    A.reserve( NN*3UL-2UL );                // Allocate the total amount of memory
//    A.reserve( 0UL, 2UL );             // Reserve a capacity of 2 for row 0
//    for( size_t i=1; i<N-1UL; ++i ) {
//        A.reserve( i, 3UL );            // Reserve a capacity of 3 for row i
//    }
//    A.reserve( N-1UL, 2UL );           // Reserve a capacity of 2 for the last row

    for( size_t i=0; i<NN; ++i ) {
//        const size_t jbegin( i == 0UL ? 0UL : i-1UL );
//        const size_t jend  ( i == NN-1UL ? NN-1UL : i+1UL );
//        for( size_t j=jbegin; j<=jend; ++j ) {
//            A.insert( i, j, 1 );
//        }
        //size_t j = i;
        A.insert( i, i, 1 );
    }
    return A;

}

void matrixOperations::fillBand(const long bandID,
                                CompressedMatrix<double, rowMajor> &A,
                                const DynamicVector<double, columnVector> &bandAr) {

    const size_t NN = bandAr.size();

    for (size_t r = 0; r < NN; ++r) {
        const size_t c = r+bandID;

        if ( c >= 0 ){
            A(r,c) = bandAr[r];
        }
    }

    // testing:
    // I define one vector with increasing values.
    // If I build the banded amtrix using this vector and different band ids
    // I should get the same number in every row.
//    blaze::DynamicVector<double,blaze::columnVector> ap( NN, 0.0 );
//    for (size_t i =0; i< ap.size(); ++i){
//        ap[i] = i+1;
//    }
//    matrixOperations::fillBand(0, A, ap); // central band
//    matrixOperations::fillBand(1, A, ap); // east band
//    matrixOperations::fillBand(-1, A, ap); // west band
//
//    matrixOperations::fillBand(-4, A, ap); // north band
//    matrixOperations::fillBand(4, A, ap); // south band

}