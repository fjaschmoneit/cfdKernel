//
// Created by fynn on 4/16/23.
//

#include "field.h"


FIELD::field::field(MESH::structured2dRegularRectangle const &mesh)
:mesh_(mesh),
fvmField_( FVM::collocatedField::createLinearizedData(mesh_)),
fieldView_(std::experimental::mdspan( fvmField_.data(), std::experimental::extents{mesh.nbCellsY, mesh.nbCellsX} ))
{}

FIELD::field::field(FIELD::field &otherField)
:mesh_(otherField.mesh_),
fvmField_( otherField.fvmField_ ),
fieldView_(std::experimental::mdspan( fvmField_.data(), std::experimental::extents{mesh_.nbCellsY, mesh_.nbCellsX} ))
{}






void FIELD::print( FIELD::field const & fieldObj ){
    auto nbR = fieldObj.fieldView_.extent(0);
    auto nbC = fieldObj.fieldView_.extent(1);

    for( auto r=0; r<nbR; ++r  ){
        std::cout << "( ";
        for( auto c=0; c<nbC; ++c ){
            std::cout << fieldObj.fieldView_(r,c) << " ";
        }
        std::cout << " )" << std::endl;
    }
}

void FIELD::print( GLOBAL::vector const & vecObj ){
    std::cout << "( " ;
    std::for_each(vecObj.begin(), vecObj.end(), [](const int& n) { std::cout << n << ' '; });
    std::cout << " )" << std::endl;
}
