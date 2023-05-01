#include "gtest/gtest.h"
#include "LINALG/matrixOperations.h"
#include "LINALG/linearEquationSolvers.h"

using namespace LINALG;

struct matrixOperationsFixture : public ::testing::Test {

    size_t length = 10;

    vector zeroVector = vector(length, 0.0);
    vector oneVector = vector(length, 1.0);

    matrix identityMatrix = matrixOperations::newIdentityMatrix(length);
    matrix zeroMatrix = matrixOperations::newZeroMatrix(length);
};

TEST_F(matrixOperationsFixture, fillbandWithEntries_identityToZeroMat){
    auto matrix = identityMatrix;

    matrixOperations::fillBand(0, matrix, zeroVector);

    EXPECT_EQ(matrix, zeroMatrix);
}

TEST_F(matrixOperationsFixture, fillbandWithEntries_zeroMatToIdentity){
    auto matrix = zeroMatrix;

    matrixOperations::fillBand(0, matrix, oneVector);

    EXPECT_EQ(matrix, identityMatrix);
}

TEST_F(matrixOperationsFixture, fillbandWithEntries_alignmentOfOffDiagonals){
    auto matrix = zeroMatrix;
    auto vec = zeroVector;
    for(int i=0; i<length; ++i){
        vec[i] = i+1;
    }

    // expecting rows:              row L1 norm
    //  (1 1 0 0 0 1 0 0 0 0)         3
    //  (2 2 2 0 0 0 2 0 0 0)         8
    //  (0 3 3 3 0 0 0 3 0 0)         12
    //  ...
    matrixOperations::fillBand(0, matrix, vec);
    matrixOperations::fillBand(1, matrix, vec);
    matrixOperations::fillBand(-1, matrix, vec);
    matrixOperations::fillBand(5, matrix, vec);

    auto r0 = blaze::row<0>(matrix);
    auto r1 = blaze::row<1>(matrix);
    auto r2 = blaze::row<2>(matrix);

    EXPECT_EQ( blaze::l1Norm(r0), 3);
    EXPECT_EQ( blaze::l1Norm(r1), 8);
    EXPECT_EQ( blaze::l1Norm(r2), 12);
}

// =====================================================
// =====================================================
struct linearEquationSolversFixture : public ::testing::Test {

    const size_t maxIterations = 1e2;
    const double convLimit = 1e-8;
    const size_t length = 10;

    const vector zeroVector = vector(length, 0.0);
    const vector oneVector = vector(length, 1.0);

    const matrix identityMatrix = matrixOperations::newIdentityMatrix(length);
    const matrix zeroMatrix = matrixOperations::newZeroMatrix(length);
};

TEST_F(linearEquationSolversFixture, conjugateGradient_trivialLinSystem){
    auto A = identityMatrix;
    auto b = oneVector;
    auto x = zeroVector;

    linearEquationSolvers::solveConjugateGradient(A, b, x, maxIterations, convLimit);

    EXPECT_EQ(x, oneVector);
}

// this test fails. Check if conjugate gradient is suitable for such problems
TEST_F(linearEquationSolversFixture, conjugateGradient_simpleBackSubstitution){
    auto A = identityMatrix;
    auto b = oneVector;
    auto x = zeroVector;
    A(0,1) = 1;

    linearEquationSolvers::solveConjugateGradient(A, b, x, maxIterations, convLimit);

    // result should be (0 1 1 1 1 1 1 1 1 1)
    auto thrSol = oneVector;
    thrSol[0] = 0;

    EXPECT_EQ(x, thrSol);
}

TEST_F(linearEquationSolversFixture, conjugateGradient_FerzingerExample1){
    size_t len(5);

    auto A = matrixOperations::newZeroMatrix(len);
    vector ap{3,2,2,2,3};
    vector ae(5,-1);
    vector aw(5,-1);
    matrixOperations::fillBand(0, A, ap); // central band
    matrixOperations::fillBand(1, A, ae); // east band
    matrixOperations::fillBand(-1, A, aw); // west band

    // building source vector:
    vector b{2*100,0,0,0,2*500};
    vector x(len, 0.0);

    linearEquationSolvers::solveConjugateGradient(A, b, x, maxIterations, convLimit);

    vector solution{140, 220, 300, 380, 460};
    EXPECT_EQ(x, solution);
}


// =====================================================
// =====================================================
struct blazeOperations : public ::testing::Test {

    size_t length = 10;

    vector zeroVector = vector(length, 0.0);
    vector oneVector = vector(length, 1.0);

    matrix identityMatrix = matrixOperations::newIdentityMatrix(length);
    matrix zeroMatrix = matrixOperations::newZeroMatrix(length);
};

TEST_F(blazeOperations, norms){
    auto vec = zeroVector;
    vec[0] = 1.0;
    vec[1] = 2.0;
    vec[5] = 3.0;

    EXPECT_EQ( blaze::l1Norm(vec), 6);
    EXPECT_EQ( blaze::sqrNorm(vec), 14);
}
