#include "gtest/gtest.h"
#include <blaze/Math.h>
//#include <blaze/Forward.h>

using namespace blaze;

struct blazeFixture : public ::testing::Test {

};

TEST_F(blazeFixture, sizeAndCapacityOfSparseMatrices){

    size_t n(100);

    // declaration of sparse and dense matrices
    CompressedMatrix<float, rowMajor> A(n,n);
    DynamicMatrix<float, rowMajor> B(n,n);

    // checking dimensions of matrices:
    EXPECT_EQ(A.rows(), n);
    EXPECT_EQ(B.rows(), n);

    // accessing not initialized elements:
    EXPECT_EQ(A(1,1), 0.);
    EXPECT_EQ(B(1,1), 0.);

    // Size returns the total nb of elements #rows * #columns. also in sparse matrices:
    EXPECT_EQ(size(A), size(B));

    // the capacity of sparse and dense matrix is not the same.
    // In dense matrices, the capacity is the same as the size.
    // I use reserve to allocate enough space for my sparse matrix
    EXPECT_NE(capacity(A), capacity(B));
    A.reserve(size(B));
    EXPECT_EQ(capacity(A), capacity(B));

    // Since I have not initialized any elements in my sparse matrix, shrinkToFit will
    // remove the earlier allocated capacity. I reserve more space and test its capacity.
    A.shrinkToFit();
    int nbSparseElements = 10;
    A.reserve(nbSparseElements);
    EXPECT_EQ(capacity(A), nbSparseElements);

    // trying to put more elements in sparse matrix than revserved:
    // the reserved capacity is expanded, when more elements are inserted than the capacity holds.
    // the added capacity is created in bunches, not elements-wise:
    for (int i=0; i<nbSparseElements+4; ++i) {
        A(i,i) = 1.0;
    }
    EXPECT_NE(capacity(A), 14);
    A.shrinkToFit();
    EXPECT_EQ(capacity(A), 14);







}


