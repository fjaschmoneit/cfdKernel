#include "gtest/gtest.h"
#include "FIELD/field.h"
#include "MESH/structured2d.h"

using namespace FIELD;

struct fieldFixture : public ::testing::Test {

    // size of physical domain
    GLOBAL::scalar lenX = 5.0;
    GLOBAL::scalar lenY = 3.0;

    // spacial discretization
    int nbCellsPerLength = 2;

    MESH::structured2dRegularRectangle mesh{lenX, lenY, nbCellsPerLength };
    int nbCells = nbCellsPerLength*lenX *nbCellsPerLength*lenY;

    field myField{mesh};
};

TEST_F(fieldFixture, iterators) {
    // always call with lengthX=1, lengthY=0.8, cellsPerMeter=5
    const MESH::structured2dRegularRectangle mesh{1., 0.8, 5};

    field T(mesh);

    for (auto ti = T.region(MESH::RegionID::Boundary_left).begin(); ti != T.region(MESH::RegionID::Boundary_left).end(); ++ti) {
        *ti = 1.;
    }

    for (auto ti = T.region(MESH::RegionID::Boundary_bottom).begin(); ti != T.region(MESH::RegionID::Boundary_bottom).end(); ++ti) {
        *ti = 2.;
    }

    for (auto ti = T.region(MESH::RegionID::Boundary_right).begin(); ti != T.region(MESH::RegionID::Boundary_right).end(); ++ti) {
        *ti = 3.;
    }

    for (auto ti = T.region(MESH::RegionID::Boundary_top).begin(); ti != T.region(MESH::RegionID::Boundary_top).end(); ++ti) {
        *ti = 4.;
    }

    for (auto ti = T.region(MESH::RegionID::Internal).begin(); ti != T.region(MESH::RegionID::Internal).end(); ++ti) {
        *ti = -1.;
    }

    auto data = T.getData();

    // artificially building a similar mesh:
    GLOBAL::vector similarField(mesh.nbCells, -1.0);

    // boundary 0
    for (int i = 0; i < mesh.nbCellsY; ++i)
        similarField[i*mesh.nbCellsX] = 1.;

    // Boundary 1
    for (int i = 0; i < mesh.nbCellsX; ++i)
        similarField[i + mesh.nbCells-mesh.nbCellsX] = 2.;

    //Boundary 2
    for (int i = 0; i < mesh.nbCellsY; ++i)
        similarField[i*mesh.nbCellsX + mesh.nbCellsY] = 3.;

    // boundary 3
    for (int i = 0; i < mesh.nbCellsX; ++i)
        similarField[i ] = 4.;

    EXPECT_EQ(data, similarField);
}


//
// TEST_F(fieldFixture, copyConstuctors) {
//     auto myFieldCopy(myField); // direct initialization
//     myFieldCopy.fieldView_(2,2) = 10;
//
//     // Verify that fields are different objects
//     EXPECT_NE(&myFieldCopy, &myField);
//     // verify that the underlying data is different
//     EXPECT_NE(myFieldCopy.fvmField_, myField.fvmField_);
// }
//
// TEST_F(fieldFixture, structuredDataView){
//     auto T(myField);
//     FVM::collocatedField::fillWithIncreasingNumbers(T.fvmField_);
//     auto nbX = size_t(lenX*nbCellsPerLength);
//     auto nbY = size_t(lenX*nbCellsPerLength);
//     size_t pos = nbCells-8;
//
//     auto r = pos/nbX;
//     auto c = pos%nbY;
//
//     EXPECT_EQ(T.fvmField_[pos], T.fieldView_(r,c));
// }
