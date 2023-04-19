//
// Created by fynn on 4/16/23.
//

#include <memory>
#include "../../extLibs/mdspan.hpp" // experimental implementation of unreleased C++23 feature mdspan

#include "../globalTypeDefs.h"
#include "fieldTypeDefs.h"

#include "../MESH/structured2d.h"
#include "../FVM/collocatedField.h"

namespace FIELD{

    class field {
    private:
        const MESH::structured2dRegularRectangle &mesh_;

    public:
        GLOBAL::vector fvmField_;
        FIELD::mat_2d fieldView_;

        // constructors:
        field(MESH::structured2dRegularRectangle const &mesh);
    };
}