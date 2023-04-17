//
// Created by fynn on 4/15/23.
//

#ifndef TESTING_DATAVIEW_H
#define TESTING_DATAVIEW_H

#endif //TESTING_DATAVIEW_H

#include <vector>
#include <memory>


// experimental implementation of unreleased C++23 feature mdspan
#include "../extLibs/mdspan.hpp"

#include "../MESH/structured2d.h"
#include "../FVM/collocatedField.h"

namespace FIELD{


    //std::experimental::mdspan<> unfoldData();

    class dataView {
    private:
        std::shared_ptr<FVM::collocatedField> fvmField_;


        //std::experimental::mdspan<> fieldView_;

    public:
        dataView( std::shared_ptr<FVM::collocatedField> fvmField );

        //std::experimental::mdspan getFieldView();

    };
}

