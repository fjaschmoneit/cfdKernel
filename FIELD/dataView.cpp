//
// Created by fynn on 4/15/23.
//

#include "dataView.h"

using namespace FIELD;

//std::experimental::mdspan dataView::unfoldData(){
//
//}


dataView::dataView(std::shared_ptr<FVM::collocatedField> fvmField )
:fvmField_( fvmField )
{

    auto dat = fvmField_->getData();
    auto mesh = fvmField_->getMesh();
    std::experimental::mdspan fieldView_( std::experimental::mdspan( dat->data(), std::experimental::extents{mesh->nbCellsY, mesh->nbCellsX} ));


//
//    std::vector<double> d1{ 0.0, 5.0, 1.0, 3.0 };
//    std::experimental::mdspan field( d1.data(), std::experimental::extents{2,2} );
////    std::cout << field(1,1) << std::endl;
//
//    std::vector<double> d{
//            0, 5, 1, 3, 8,
//            4, 2, 7, 6, 2
//    };
//    field = std::experimental::mdspan( d.data(), std::experimental::extents{2,5} );
////    std::cout << field(1,3) << std::endl;

}

std::experimental::mdspan dataView::getFieldView() {
    return field_;
}
