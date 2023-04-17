//
// Created by fynn on 4/10/23.
//

#include "collocatedField.h"

using namespace FVM;

// default constructor
collocatedField::collocatedField( std::shared_ptr<MESH::structured2dRegularRectangle> meshPointer )
:mesh_(meshPointer),
data_( std::make_shared<std::vector<double>>( std::vector<double>(mesh_->nbCells, 0.0)))
{

//    auto field = std::experimental::mdspan(raw.data(), pMesh->nbCellsY, pMesh->nbCellsX);
//
//    // write data using 2D view
//    for(size_t i=0; i != ms2.extent(0); i++)
//        for(size_t j=0; j != ms2.extent(1); j++)
//            ms2[i, j] = i*1000 + j;
//
//    // read back using 3D view
//    for(size_t i=0; i != ms3.extent(0); i++)
//    {
//        fmt::print("slice @ i = {}\n", i);
//        for(size_t j=0; j != ms3.extent(1); j++)
//        {
//            for(size_t k=0; k != ms3.extent(2); k++)
//                fmt::print("{} ",  ms3[i, j, k]);
//            fmt::print("\n");
//        }
//    }


//
//    for( size_t i = 0; i<pMesh->nbCellsY; ++i  ){
//        data[i] = std::vector<double>(pMesh->nbCellsX, 0.0);
//    }

}

std::shared_ptr<std::vector<double>> collocatedField::getData() {
    return data_;
}

std::shared_ptr<MESH::structured2dRegularRectangle> collocatedField::getMesh() {
    return mesh_;
}
