//
// Created by fynn on 4/16/23.
//

#include "field.h"

using namespace FIELD;

field::field(std::shared_ptr<MESH::structured2dRegularRectangle> mesh)
:mesh_(std::move(mesh)),
fvmField_(std::make_shared<FVM::collocatedField>(FVM::collocatedField(mesh_))),
dataView_( std::make_shared<FIELD::dataView>(FIELD::dataView(fvmField_ )))
{
}

