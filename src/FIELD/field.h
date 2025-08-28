// #include <memory>
// #include <iostream>
// I don't think i need this
// #include "../../extLibs/mdspan.hpp" // experimental implementation of unreleased C++23 feature mdspan
#include "../globalTypeDefs.h"
// #include "fieldTypeDefs.h"
#include "../MESH/structured2d.h"
// #include "../FVM/collocatedField.h"
#include "fieldView.h"


namespace FIELD{

    class field {
    private:
        const MESH::structured2dRegularRectangle &mesh_;
        GLOBAL::vector data_;

    public:
        // constructor on any mesh type to be implemented:
        field(MESH::structured2dRegularRectangle const &mesh)
        :mesh_(mesh),
         data_(std::vector<GLOBAL::scalar>(mesh.nbCells(), 0.))
        {}

        GLOBAL::scalar& operator[](unsigned int cell) { return data_[cell]; }
        const GLOBAL::scalar& operator[](unsigned int cell) const { return data_[cell]; }

        FieldViewRange region( MESH::RegionID regionID ) {
            return FieldViewRange( mesh_.region(regionID), &data_ );
        }

        const GLOBAL::vector& getData() const {
            return data_;
        }
    };
}