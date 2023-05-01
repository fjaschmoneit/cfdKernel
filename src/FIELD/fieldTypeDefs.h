//
// Created by fynne on 4/17/23.
//

#include "../globalTypeDefs.h"
#include "../../extLibs/mdspan.hpp" // experimental implementation of unreleased C++23 feature mdspan


namespace FIELD{
    using mat_2d = std::experimental::mdspan<GLOBAL::scalar, std::experimental::dextents<size_t, 2> >;

}