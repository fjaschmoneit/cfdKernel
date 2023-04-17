//
// Created by fynn on 4/12/23.
//

#include "structured2d.h"

using namespace MESH;

structured2dRegularRectangle::structured2dRegularRectangle(double lengthX, double lengthY, size_t cellsPerMeter)
        : lenX(lengthX),
          lenY(lengthY),
          cellsPerLength(cellsPerMeter),
          nbCellsX( size_t(lengthX*double(cellsPerMeter)) ),
          nbCellsY( size_t(lengthY*double(cellsPerMeter)) ),
          nbCells( nbCellsX*nbCellsY )
{

}

// testing :
//std::cout << myMesh.nbCells << std::endl;
//std::cout << myMesh.nbCellsX << std::endl;
//std::cout << myMesh.nbCellsY << std::endl;
//std::cout << myMesh.cellsPerLength << std::endl;
//std::cout << myMesh.lenX << std::endl;
//std::cout << myMesh.lenY << std::endl;
