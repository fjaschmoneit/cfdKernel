//
// Created by fynn on 4/12/23.
//

#include "structured2d.h"

using namespace MESH;

// constructor
structured2dRegularRectangle::structured2dRegularRectangle(float lengthX, float lengthY, int cellsPerMeter)
        : lenX(lengthX),
          lenY(lengthY),
          cellsPerLength(cellsPerMeter),
          nbCellsX( (unsigned int) (lengthX*double(cellsPerMeter)) ),
          nbCellsY( (unsigned int) (lengthY*double(cellsPerMeter)) ),
          nbCells( nbCellsX*nbCellsY )
{
    if (nbCellsX < 2 || nbCellsY < 2)
        throw std::runtime_error("Mesh dimensions must be >= 2");

    // Initialize boundaries container with 4 sides for a rectangle: 0=bottom,1=left,2=top,3=right
    fillBoundaries();
    fillInternalCells();
}


void structured2dRegularRectangle::fillBoundaries(){
    regions[RegionID::Boundary_left].cells.resize(nbCellsY);
    regions[RegionID::Boundary_bottom].cells.resize(nbCellsX);
    regions[RegionID::Boundary_right].cells.resize(nbCellsY);
    regions[RegionID::Boundary_top].cells.resize(nbCellsX);

    // Left boundary #0 (i = 0..nbY-1, j = 0)
    for (int i = 0; i < nbCellsY; ++i) {
        regions[RegionID::Boundary_left].cells[i] = i * nbCellsX;
    }

    // Bottom boundary #1 (i = nbY-1, j = 0...nbX-1)
    for (int j = 0; j < nbCellsX; ++j) {
        regions[RegionID::Boundary_bottom].cells[j] = j + (nbCellsY -1)*nbCellsX;
    }

    // Right boundary #2 (i = 0..nbY-1, j = nbX-1)
    for (int i = 0; i < nbCellsY; ++i) {
        regions[RegionID::Boundary_right].cells[i] = nbCellsX-1 + (nbCellsY -1)*nbCellsX -i*nbCellsX;
    }

    // Top boundary #3 (i = 0, j = 0..nbCellsX-1)
    for (int j = 0; j < nbCellsX; ++j) {
        regions[RegionID::Boundary_top].cells[j] = nbCellsX-1-j;
    }
}

bool structured2dRegularRectangle::isBoundaryCell( unsigned int cell ) const {
        unsigned int i = cell % nbCellsX;
        unsigned int j = cell / nbCellsX;
        return i == 0 || i == nbCellsX - 1 || j == 0 || j == nbCellsY - 1;
}

void structured2dRegularRectangle::fillInternalCells() {
    regions[RegionID::Internal].cells.resize( nbCells - (2*nbCellsX+2*nbCellsY-4) );

    unsigned int counter = 0;
    for (int icell = 0; icell < nbCells; ++icell) {
        if ( !isBoundaryCell(icell)) {
            regions[RegionID::Internal].cells[counter] = icell;
            counter++;
        }
    }
}

