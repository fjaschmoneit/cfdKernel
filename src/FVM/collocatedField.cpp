//
// Created by fynn on 4/10/23.
//

#include "collocatedField.h"

using namespace FVM;

std::vector<GLOBAL::scalar> collocatedField::createLinearizedData( MESH::structured2dRegularRectangle const &mesh ){
    return {std::vector<GLOBAL::scalar>(mesh.nbCells, 0.0)};
}

