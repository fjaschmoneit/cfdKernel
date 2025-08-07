#include "matrixOperations.h"

#include <iostream>

using namespace LINALG;

CompressedMatrix<GLOBAL::scalar,rowMajor> matrixOperations::newZeroMatrix(const size_t NN){
    return { NN, NN };
}

CompressedMatrix<GLOBAL::scalar,rowMajor> matrixOperations::newIdentityMatrix(const size_t NN){

    CompressedMatrix<GLOBAL::scalar,rowMajor> A( NN, NN );
    A.reserve( NN );
    // vector ones(NN,1.0);

    band(A,0) = vector(NN,1.0);
    // fillBand(0, A, ones);

    return A;
}

 matrix matrixOperations::invertLowerTriangularBandMatrix(const matrix &A) {

    const size_t n = A.rows();
    matrix B(n, n);

    // filling
    for (size_t k = 0; k < n; ++k) {
        // this is the k-th column of the inverse matrix
        vector b_k(n, 0.0);

        // the element, which will lie on the eventual diagonal is initialized with 1.
        b_k[k] = 1.;

        // Forward substitution within the band
        for (size_t r = k; r < n; ++r) {

            // Only consider entries in the band [i - bandwidth, i]
            GLOBAL::scalar sum = 0.;

            // this iterates through the entire column, but i know, at which indices my non-zero entries are.
            for (auto it = A.begin(r); it != A.end(r); ++it) {
                size_t j = it->index();

                if (j < k || j >= r)
                    continue;

                sum += it->value() * b_k[j];
            }

            // is r on diagonal? then write 1./Aii, otherwise -sum/Aii
            if (r == k)
                b_k[r] = 1. / A(r, r);
            else
                b_k[r] = -sum / A(r, r);
        }

        // Storing column b in B, neglecting zero entries
        for (size_t r = k; r < n; ++r) {
            if (b_k[r] != 0) {
                B(r, k) = b_k[r];
            }
        }
    }
    return B;
}

void matrixOperations::getUpperTriangularBandIndices(const CompressedMatrix<GLOBAL::scalar, rowMajor> &A,
                                                     std::vector<int> &indices) {

    int rowTicker = 0;
    for(CompressedMatrix<GLOBAL::scalar,rowMajor>::ConstIterator i=A.begin(0); i!=A.end(0); ++i ) {
        int a = i->index();  // Access to the index of the non-zero element
        indices[rowTicker] = a;
        rowTicker++;
    }
    indices.erase(std::remove(indices.begin(), indices.end(), 0), indices.end());
}


void matrixOperations::copyBandElements(Band<const CompressedMatrix<GLOBAL::scalar>,false,false,false> srcBand, Band<CompressedMatrix<GLOBAL::scalar>,false,false,false> trgBand) {
    for (size_t i = 0; i < srcBand.size(); ++i) {
        trgBand[i] = srcBand[i];
    }
}


