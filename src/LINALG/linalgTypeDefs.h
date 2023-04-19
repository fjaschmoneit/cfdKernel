//
// Created by fynne on 4/17/23.
//

#include "../globalTypeDefs.h"
#include <blaze/Forward.h>
#include <blaze/Math.h>

namespace LINALG{

    using vector = blaze::DynamicVector<GLOBAL::scalar, blaze::columnVector>;
    using matrix = blaze::CompressedMatrix<GLOBAL::scalar, blaze::rowMajor>;

}