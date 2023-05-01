#include "gtest/gtest.h"
#include "FVM/coefficientMatrixGenerator.h"
#include "MESH/structured2d.h"
#include "LINALG/linalgTypeDefs.h"

using namespace FVM;

struct coefficientMatrixGeneratorFixture : public ::testing::Test {

    MESH::structured2dRegularRectangle mesh { 5.0, 4.0, 3 };
    coefficientMatrixGenerator coeffGen { mesh };

    LINALG::matrix zeroMat = LINALG::matrixOperations::newZeroMatrix(mesh.nbCells);
    LINALG::matrix identityMat = LINALG::matrixOperations::newIdentityMatrix(mesh.nbCells);
    LINALG::vector zeroVector = LINALG::vector(mesh.nbCells, 0.0);
    LINALG::vector oneVector = LINALG::vector(mesh.nbCells, 1.0);
};

TEST_F(coefficientMatrixGeneratorFixture, defaultCoeffMatrix){
    auto coeffMat = zeroMat;
    auto constVec = zeroVector;

    coeffGen.assembleCoeffMatrix( coeffMat );
    coeffGen.assembleConstVec( constVec );

    EXPECT_EQ(coeffMat, identityMat);
    EXPECT_EQ(constVec, oneVector);
}

TEST_F(coefficientMatrixGeneratorFixture, setDirectionalFlux) {
    auto nbX(mesh.nbCellsX);
    auto coeffMat = zeroMat;
    GLOBAL::vector ap(mesh.nbCells, 2.0);
    GLOBAL::vector ae(mesh.nbCells, 3.0);
    GLOBAL::vector aw(mesh.nbCells, 4.0);
    GLOBAL::vector an(mesh.nbCells, 5.0);
    GLOBAL::vector as(mesh.nbCells, 6.0);

    coeffGen.setDirectionalFlux( ap, FVM::CardinalDirection::centre );
    coeffGen.setDirectionalFlux( aw, FVM::CardinalDirection::west );
    coeffGen.setDirectionalFlux( ae, FVM::CardinalDirection::east );
    coeffGen.setDirectionalFlux( as, FVM::CardinalDirection::south );
    coeffGen.setDirectionalFlux( an, FVM::CardinalDirection::north );
    coeffGen.assembleCoeffMatrix( coeffMat );

    // expected coeff matrix:   row sum:
    // (2 3 ... 6 ...    )      11
    // (4 2 3 ... 6 ...  )      15
    // (0 4 2 3 ... 6 ...)      15
    // (:::              )

    auto sumRow0 = coeffMat(0,0) +coeffMat(0,1) +coeffMat(0,nbX);
    auto sumRow1 = coeffMat(1,0) +coeffMat(1,1) +coeffMat(1,2) +coeffMat(1,nbX+1);
    auto sumRowNbX = coeffMat(nbX,0) +coeffMat(nbX,nbX-1) +coeffMat(nbX,nbX) +coeffMat(nbX,nbX+1) + coeffMat(nbX,2*nbX);
    auto sumRowNbXp1 = coeffMat(nbX+1,1) +coeffMat(nbX+1,nbX) +coeffMat(nbX+1,nbX+1) +coeffMat(nbX+1,nbX+2) + coeffMat(nbX+1,2*nbX+1);

    EXPECT_EQ( sumRow0 , 11.0  );
    EXPECT_EQ( sumRow1 , 15.0  );
    EXPECT_EQ( sumRowNbX , 20.0  );
    EXPECT_EQ( sumRowNbXp1 , 20.0  );
}