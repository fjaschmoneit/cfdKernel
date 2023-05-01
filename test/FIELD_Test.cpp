#include "gtest/gtest.h"
#include "FIELD/field.h"
#include "MESH/structured2d.h"


using namespace FIELD;

struct fieldFixture : public ::testing::Test {

    // size of physical domain
    GLOBAL::scalar lenX = 5.0;
    GLOBAL::scalar lenY = 3.0;

    // spacial discretization
    size_t nbCellsPerLength = 2;

    MESH::structured2dRegularRectangle mesh{lenX, lenY, nbCellsPerLength };
    size_t nbCells = nbCellsPerLength*lenX *nbCellsPerLength*lenY;

    field myField{mesh};
};

TEST_F(fieldFixture, copyConstuctors) {
    auto myFieldCopy(myField); // direct initialization
    myFieldCopy.fieldView_(2,2) = 10;

    // Verify that fields are different objects
    EXPECT_NE(&myFieldCopy, &myField);
    // verify that the underlying data is different
    EXPECT_NE(myFieldCopy.fvmField_, myField.fvmField_);
}

TEST_F(fieldFixture, structuredDataView){
    auto T(myField);
    FVM::collocatedField::fillWithIncreasingNumbers(T.fvmField_);
    auto nbX = size_t(lenX*nbCellsPerLength);
    auto nbY = size_t(lenX*nbCellsPerLength);
    size_t pos = nbCells-8;

    auto r = pos/nbX;
    auto c = pos%nbY;

    EXPECT_EQ(T.fvmField_[pos], T.fieldView_(r,c));
}
