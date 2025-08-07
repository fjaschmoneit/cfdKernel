#include "gtest/gtest.h"
#include "MESH/structured2d.h"


struct meshFixture : public ::testing::Test {

    // a rectangular mesh with (nbX,nbY)=(5,4) cells
    // its cell and boundary indices are illustrated here:
    //
    //               3
    //     +----+----+----+----+----+
    //     |  0 |  1 |  2 |  3 |  4 |
    //     +----+----+----+----+----+
    //     |  5 |  6 |  7 |  8 |  9 |
    //  0  +----+----+----+----+----+    2
    //     | 10 | 11 | 12 | 13 | 14 |
    //     +----+----+----+----+----+
    //     | 15 | 16 | 17 | 18 | 19 |
    //     +----+----+----+----+----+
    //               1
    const MESH::structured2dRegularRectangle mesh{1., 0.8, 5};
};


// it would be nice, if I hadn't to save an entire field with indices.
// the iterators would just have to work on calculated entries
TEST_F(meshFixture, meshCellIterators) {

    auto leftBoundary = mesh.getRegion(MESH::RegionID::Boundary_left);
    auto bottomBoundary = mesh.getRegion(MESH::RegionID::Boundary_bottom);
    auto rightBoundary = mesh.getRegion(MESH::RegionID::Boundary_right);
    auto topBoundary = mesh.getRegion(MESH::RegionID::Boundary_top);
    auto internal = mesh.getRegion(MESH::RegionID::Internal);

    // checking iterators on boundaries
    EXPECT_EQ(*leftBoundary.last(), 15);
    EXPECT_EQ(*bottomBoundary.begin(), 15);
    EXPECT_EQ(*bottomBoundary.last(), 19);
    EXPECT_EQ(*rightBoundary.last(), 4);

    // checking iterators on insinde:
    EXPECT_EQ(*internal.begin(), 6);
    EXPECT_EQ(*(internal.begin()+1), 7);
    EXPECT_EQ(*(internal.begin()+3), 11);
    EXPECT_EQ(*(internal.end()-1), 13);
    EXPECT_EQ(*(internal.last()), 13);
}

