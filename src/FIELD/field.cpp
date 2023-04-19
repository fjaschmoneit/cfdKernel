//
// Created by fynn on 4/16/23.
//

#include "field.h"

using namespace FIELD;

field::field(MESH::structured2dRegularRectangle const &mesh)
:mesh_(mesh),
fvmField_( FVM::collocatedField::createLinearizedData(mesh_)),
fieldView_(std::experimental::mdspan( fvmField_.data(), std::experimental::extents{mesh.nbCellsY, mesh.nbCellsX} ))
{
}

