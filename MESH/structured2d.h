//
// Created by fynn on 4/12/23.
//

#ifndef TESTING_STRUCTURED2D_H
#define TESTING_STRUCTURED2D_H

#endif //TESTING_STRUCTURED2D_H
#pragma once

#include <cstddef>

#include "baseMesh.h"

namespace MESH {

    class structured2dRegularRectangle: public baseMesh {

    public:

        // order must follow initialization list
        const double lenX;
        const double lenY;
        const size_t cellsPerLength;
        const size_t nbCellsX;
        const size_t nbCellsY;
        const size_t nbCells;


        structured2dRegularRectangle(double lengthX, double lengthY, size_t cellsPerMeter);
        ~structured2dRegularRectangle() override = default;

    };

}