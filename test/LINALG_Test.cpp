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

    auto A = identityMatrix;
    band(A,0) = zeroVector;
    EXPECT_EQ(A, zeroMatrix);

    auto B = zeroMatrix;
    band(B,0) = oneVector;
    EXPECT_EQ(B, identityMatrix);
}


// Consider defining L,U,D matrices from the start, lower, upper, diagonal. Only if necessary add them together.
TEST_F(matrixOperationsFixture, fillbandWithEntries_alignmentOfOffDiagonals){
    auto A = zeroMatrix;
    auto vec = zeroVector;
    for(int i=0; i<length; ++i){
        vec[i] = i+1;
    }

    // expecting rows:              row L1 norm
    //  (1 1 0 0 0 1 0 0 0 0)         3
    //  (1 2 2 0 0 0 2 0 0 0)         7
    //  (0 2 3 3 0 0 0 3 0 0)         11
    //  ...

    band(A,0) = vec;
    band(A,1) = subvector(vec, 0, length-1);
    band(A,-1) = subvector(vec, 0, length-1);
    band(A,5) = subvector(vec, 0, length-5);

    auto r0 = blaze::row<0>(A);
    auto r1 = blaze::row<1>(A);
    auto r2 = blaze::row<2>(A);

    EXPECT_EQ( blaze::l1Norm(r0), 3);
    EXPECT_EQ( blaze::l1Norm(r1), 7);
    EXPECT_EQ( blaze::l1Norm(r2), 11);
}


// redundant??
TEST_F(matrixOperationsFixture, getUpperDiagonalBands) {
    auto A = zeroMatrix;

    std::vector<int> specifiedBandIndices{0,1,-1,5,-5};
    std::for_each(specifiedBandIndices.begin(), specifiedBandIndices.end(),
        [&](const int n) {
            band(A,n) = vector(A.rows()-abs(n), 1);
        });

    std::vector<int> indices;
    indices.resize(7);   // 7 is neighbor number in 3D
    matrixOperations::getUpperTriangularBandIndices( A, indices );

    std::vector<int> correctIndices{1,5};
    EXPECT_EQ( indices, correctIndices);
}


TEST_F(matrixOperationsFixture, invertLowerTriangularBandMatrix) {

    // defining bands in A matrix:
    auto A = zeroMatrix;
    std::vector<int> bandIndices{0,-3,-4};
    std::for_each(bandIndices.begin(), bandIndices.end(), [&](const int& index) {
        auto a = band(A, index);
        a = vector(length-abs(index), abs(index)+2);
    });

    auto B = matrixOperations::invertLowerTriangularBandMatrix(A);

    // EXPECT_EQ(A, B );
    EXPECT_EQ(A*B, identityMatrix );
}


// =====================================================
// =====================================================
struct linearEquationSolversFixture : public ::testing::Test {

    const size_t maxIterations = 1e3;
    const double convLimit = 1e-8;
    const size_t length = 10;

    const vector zeroVector = vector(length, 0.0);
    const vector oneVector = vector(length, 1.0);

    const matrix identityMatrix = matrixOperations::newIdentityMatrix(length);
    const matrix zeroMatrix = matrixOperations::newZeroMatrix(length);
};

TEST_F(linearEquationSolversFixture, gaussSeidel_trivialLinSystem) {
    auto A = identityMatrix;
    auto b = oneVector;
    auto x = zeroVector;

    linearEquationSolvers::solveGaussSeidel(A, std::vector<int>{0}, b, x, maxIterations, convLimit);

    EXPECT_EQ(x, oneVector);
}

TEST_F(linearEquationSolversFixture, gaussSeidel_simpleBackSubstitution){
    auto A = identityMatrix;
    auto b = oneVector;
    auto x = zeroVector;
    A(0,1) = 1;

    linearEquationSolvers::solveGaussSeidel(A, std::vector<int>{0,1}, b, x, maxIterations, convLimit);

    // result should be (0 1 1 1 1 1 1 1 1 1)
    auto thrSol = oneVector;
    thrSol[0] = 0;

    EXPECT_EQ(x, thrSol);
}

// see Andreas Meister's book 'Numerik linearer Gleichungssysteme, p40.
TEST_F(linearEquationSolversFixture, gaussSeidel_MeisterExample) {
    size_t n = 2;

    CompressedMatrix<GLOBAL::scalar, rowMajor> A(n,n);

    A(0,0) = 0.7;
    A(0,1) = -0.4;
    A(1,0) = -0.2;
    A(1,1) = 0.5;

    vector x(2, 0);
    x[0] = 21.;
    x[1] = 19.;

    vector b(2,0.3);

    linearEquationSolvers::solveGaussSeidel(A, std::vector<int>{-1,0,1}, b, x, 100, 1e-7);

    EXPECT_FLOAT_EQ( x[0], 1. );
    EXPECT_FLOAT_EQ( x[1], 1. );
}


TEST_F(linearEquationSolversFixture, gaussSeidel_1DPoissonEQ) {

    size_t n = 50;
    GLOBAL::scalar h = 1./(n-1);

    CompressedMatrix<GLOBAL::scalar, rowMajor> A(n, n);
    std::vector<int> bands{-1,0,1};

    vector u(n, 0.1);
    vector b(n, 0.);

    // defining diagonal:
    band(A,0) = vector(n, 2);
    A(0,0) = 1.;
    A(n-1,n-1) = 1.;

    // defining first off-diagonal:
    band(A,bands[2]) = vector(n-abs(bands[2]), -1);
    A(0,1) = 0.;

    // defining second off-diagonal:
    band(A,bands[0]) = vector(n-abs(bands[0]), -1);
    A(n-1,n-2) = 0.;

    for (int i=1; i<n-1; i++) {
        b[i] =  M_PI*M_PI*h*h*sin(i*M_PI*h);
    }

    linearEquationSolvers::solveGaussSeidel(A, bands, b, u, 10000, 1e-6);

    vector theoreticalSolution(n, 0.);
    for (int i=1; i<n-1; i++) {
        theoreticalSolution[i] =  sin(i*M_PI*h);
    }

    // how near we get to the theoretical solution depends on the number of cells.
    // also, the floating point precision influences how close we can get to a solution.
    // but nevertheless, despite a deviance from the theoretical solution of O(1e-4),
    // the residual is as low as 1e-6
    for (int i=0; i< n; ++i) {
        EXPECT_NEAR( u[i], theoreticalSolution[i], 2e-4 );
    }
}


TEST_F(linearEquationSolversFixture, conjugateGradient_trivialLinSystem){
    auto A = identityMatrix;
    auto b = oneVector;
    auto x = zeroVector;

    linearEquationSolvers::solveConjugateGradient(A, b, x, maxIterations, convLimit);

    EXPECT_EQ(x, oneVector);
}

// this test throws an error. Conjugate gradient is not suitable
// for such problems as A is not symmetric
TEST_F(linearEquationSolversFixture, conjugateGradient_simpleBackSubstitution){
    auto A = identityMatrix;
    auto b = oneVector;
    auto x = zeroVector;
    A(0,1) = 1;

    EXPECT_THROW(
        {linearEquationSolvers::solveConjugateGradient(A, b, x, maxIterations, convLimit);},
        std::runtime_error);
}

TEST_F(linearEquationSolversFixture, conjugateGradient_FerzingerExample1){
    size_t len(5);

    auto A = matrixOperations::newZeroMatrix(len);
    vector ap{3,2,2,2,3};
    vector ae(4,-1);
    vector aw(4,-1);

    band(A,0) = ap;
    band(A,1) = ae;
    band(A,-1) = aw;
    // matrixOperations::fillBand(0, A, ap); // central band
    // matrixOperations::fillBand(1, A, ae); // east band
    // matrixOperations::fillBand(-1, A, aw); // west band

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
