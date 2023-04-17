//
// Created by fynn on 4/16/23.
//

#ifndef TESTING_FIELD_H
#define TESTING_FIELD_H

#endif //TESTING_FIELD_H

#include <memory>

#include "../MESH/structured2d.h"
#include "../FVM/collocatedField.h"
#include "dataView.h"

namespace FIELD{

    class field {
    private:

        std::shared_ptr<MESH::structured2dRegularRectangle> mesh_;
        std::shared_ptr<FVM::collocatedField> fvmField_;
        std::shared_ptr<FIELD::dataView> dataView_;

    public:
        field(std::shared_ptr<MESH::structured2dRegularRectangle> mesh);

};
}