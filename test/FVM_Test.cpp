#include "gtest/gtest.h"
#include "FVM/linEqSystem.h"
#include "MESH/structured2d.h"
#include "LINALG/linalgTypeDefs.h"

using namespace FVM;

struct coefficientMatrixGeneratorFixture : public ::testing::Test {

    MESH::structured2dRegularRectangle mesh { 5.0, 4.0, 1 };
    linEqSystem linsys { mesh };

    // FJA newZeroMatrix should not be a 'matrix operation' but called similarly to zeroVector
    LINALG::matrix zeroMat = LINALG::matrixOperations::newZeroMatrix(mesh.nbCells);
    LINALG::matrix identityMat = LINALG::matrixOperations::newIdentityMatrix(mesh.nbCells);
    LINALG::vector zeroVector = LINALG::vector(mesh.nbCells, 0.0);
    LINALG::vector oneVector = LINALG::vector(mesh.nbCells, 1.0);
};

TEST_F(coefficientMatrixGeneratorFixture, defaultCoeffMatrix){

    auto coeffMat = linsys.getMatrix();
    linsys.setConstVec( std::vector<GLOBAL::scalar>(coeffMat.rows(), 0. ) );

    auto sourceVec(linsys.getSourceVector());

    EXPECT_EQ(coeffMat, identityMat);
    EXPECT_EQ(sourceVec, zeroVector);
}

// this is essentially the same test as 'TEST_F(matrixOperationsFixture, fillbandWithEntries_alignmentOfOffDiagonals)'
// but here we also test the interface between std::vector types and their implementation in to a coeff matrix.
TEST_F(coefficientMatrixGeneratorFixture, setDirectionalFlux) {
    auto nbX(mesh.nbCellsX);

    // my a_i are full length:
    GLOBAL::vector ap(mesh.nbCells, 2.0);
    GLOBAL::vector ae(mesh.nbCells, 3.0);
    GLOBAL::vector aw(mesh.nbCells, 4.0);
    GLOBAL::vector an(mesh.nbCells, 5.0);
    GLOBAL::vector as(mesh.nbCells, 6.0);

    // expected coeff matrix:   row sum:
    // (2 3 ... 6 ...    )      11
    // (4 2 3 ... 6 ...  )      15
    // (0 4 2 3 ... 6 ...)      15
    // (:::              )

    linsys.setDirectionalFlux( ap, FVM::CardinalDirection::centre );
    linsys.setDirectionalFlux( aw, FVM::CardinalDirection::west );
    linsys.setDirectionalFlux( ae, FVM::CardinalDirection::east );
    linsys.setDirectionalFlux( as, FVM::CardinalDirection::south );
    linsys.setDirectionalFlux( an, FVM::CardinalDirection::north );

    auto coeffMat = linsys.getMatrix();

    auto sumRow0 = sum(row(coeffMat,0));
    auto sumRow1 = sum(row(coeffMat,1));
    auto sumRowNbX = sum(row(coeffMat,nbX));
    auto sumRowNbXp1 = sum(row(coeffMat,nbX+1));

    EXPECT_EQ( sumRow0 , 11.0  );
    EXPECT_EQ( sumRow1 , 15.0  );
    EXPECT_EQ( sumRowNbX , 20.0  );
    EXPECT_EQ( sumRowNbXp1 , 20.0  );
}