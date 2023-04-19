//
// Created by fynn on 4/10/23.
//

#ifndef TESTING_COLLOCATEDFIELD_H
#define TESTING_COLLOCATEDFIELD_H

#include <memory>
#include <vector>

#include "../globalTypeDefs.h"
#include "../MESH/structured2d.h"

namespace FVM {

    namespace collocatedField {
        GLOBAL::vector createLinearizedData(MESH::structured2dRegularRectangle const &mesh);

//        collocatedField( MESH::structured2dRegularRectangle const &mesh );

    };

};


#endif //TESTING_COLLOCATEDFIELD_H
