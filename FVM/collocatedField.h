//
// Created by fynn on 4/10/23.
//

#ifndef TESTING_COLLOCATEDFIELD_H
#define TESTING_COLLOCATEDFIELD_H

#include <memory>
#include <vector>
#include <array>


#include "../MESH/structured2d.h"

namespace FVM {

    class collocatedField {
    private:
        std::shared_ptr<MESH::structured2dRegularRectangle> mesh_;
        std::shared_ptr<std::vector<double>> data_;

    public:
//        std::experimental::mdspan<float const, std::experimental::dextents<size_t, 2>> field;

        collocatedField( std::shared_ptr<MESH::structured2dRegularRectangle> meshPointer );
        std::shared_ptr<std::vector<double>> getData();
        std::shared_ptr<MESH::structured2dRegularRectangle> getMesh();

    };

};


#endif //TESTING_COLLOCATEDFIELD_H
