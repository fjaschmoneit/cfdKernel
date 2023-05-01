#include <memory>
#include <iostream>

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
        field(MESH::structured2dRegularRectangle const &mesh);

        field(field &otherField);

        // why public?
        GLOBAL::vector fvmField_;  // change name to data?
        FIELD::mat_2d fieldView_;


    };

    void print( FIELD::field const & fieldObj );
    void print( GLOBAL::vector const & vecObj );
}