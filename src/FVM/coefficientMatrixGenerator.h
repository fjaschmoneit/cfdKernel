
#include "collocatedField.h"
#include "LINALG/matrixOperations.h"
#include "LINALG/linalgTypeDefs.h"
#include <memory>
#include <string>

namespace FVM{

    enum class CardinalDirection {centre, west, east, north, south };

    class coefficientMatrixGenerator{
    private:

        std::shared_ptr<MESH::structured2dRegularRectangle> pmesh_;

        LINALG::vector aw_;
        LINALG::vector ae_;
        LINALG::vector an_;
        LINALG::vector as_;
        LINALG::vector ap_;
        LINALG::vector b_;

    public:
        coefficientMatrixGenerator( MESH::structured2dRegularRectangle const &mesh );

        void setDirectionalFlux( GLOBAL::vector & ai, CardinalDirection dir );
        void setConstVec( GLOBAL::vector & ai );
        void assembleCoeffMatrix( LINALG::matrix & coefficientMatrix );
        void assembleConstVec( LINALG::vector & vec );
    };

}