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
    const MESH::structured2dRegularRectangle mesh{1., 5, 0.8, 4};
};


// it would be nice, if I hadn't to save an entire field with indices.
// the iterators would just have to work on calculated entries
TEST_F(meshFixture, meshCellIterators) {

    auto leftBoundary = mesh.region(MESH::RegionID::Boundary_left);
    auto bottomBoundary = mesh.region(MESH::RegionID::Boundary_bottom);
    auto rightBoundary = mesh.region(MESH::RegionID::Boundary_right);
    auto topBoundary = mesh.region(MESH::RegionID::Boundary_top);
    auto entire = mesh.region(MESH::RegionID::Entire);

    EXPECT_EQ(*leftBoundary.begin(), 0);
    EXPECT_EQ(*leftBoundary.last(), 15);

    // checking iterators on boundaries
    EXPECT_EQ(*leftBoundary.last(), 15);
    EXPECT_EQ(*bottomBoundary.begin(), 15);
    EXPECT_EQ(*std::next(bottomBoundary.begin(), 2), 17);
    EXPECT_EQ(*bottomBoundary.last(), 19);
    EXPECT_EQ(*rightBoundary.last(), 4);

    // checking iterators on insinde:
    EXPECT_EQ(*entire.begin(), 0);
    EXPECT_EQ(*std::next(entire.begin(),1), 1);
    EXPECT_EQ(*std::next(entire.begin(),3), 3);
    EXPECT_EQ(*std::next(entire.begin(),mesh.nbCells()-1), 19);
    EXPECT_EQ(*(entire.last()), 19);
}

TEST_F(meshFixture, cellCenterCoordiantes) {

    auto lx(mesh.lenX());
    auto ly(mesh.lenY());
    auto nx(mesh.nbCellsX());
    auto ny(mesh.nbCellsY());

    GLOBAL::vector cellCenters_x(mesh.nbCells(), 0);
    GLOBAL::vector cellCenters_y(mesh.nbCells(), 0);

    std::ranges::for_each( mesh.region(MESH::RegionID::Entire),
        [&](auto q) {
            cellCenters_x[q] = mesh.getCellCenterCoordinate_X(q);
            cellCenters_y[q] = mesh.getCellCenterCoordinate_Y(q);
        } );

    auto dx = 1./mesh.getCellReciprocalSpacing_X();

    EXPECT_FLOAT_EQ(cellCenters_x[0], 0.5*dx);
    EXPECT_FLOAT_EQ(cellCenters_x[1], 3./2.*dx);
    EXPECT_FLOAT_EQ(cellCenters_x[mesh.nbCellsX()-1], mesh.lenX()-0.5*dx);
    EXPECT_FLOAT_EQ(cellCenters_x[16], 3./2.*dx);

    // dx = dy
    EXPECT_FLOAT_EQ(cellCenters_y[0], 0.5*dx);
    EXPECT_FLOAT_EQ(cellCenters_y[1], 0.5*dx);
    EXPECT_FLOAT_EQ(cellCenters_y[3*mesh.nbCellsX()-2], 2.5*dx);
    EXPECT_FLOAT_EQ(cellCenters_y[16], mesh.lenY()-0.5*dx);
}