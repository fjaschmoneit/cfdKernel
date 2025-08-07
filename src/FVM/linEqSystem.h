
#include "collocatedField.h"
#include "LINALG/matrixOperations.h"
#include "LINALG/linalgTypeDefs.h"
#include "LINALG/linearEquationSolvers.h"
#include <memory>
#include <string>

namespace FVM{

    enum class CardinalDirection {centre, west, east, north, south };

    class linEqSystem{
    private:

        std::shared_ptr<MESH::structured2dRegularRectangle> pmesh_;
        LINALG::matrix A_;
        std::vector<int> bands_;
        blaze::Band<LINALG::matrix> ap_;
        blaze::Band<LINALG::matrix> ae_;
        blaze::Band<LINALG::matrix> aw_;
        blaze::Band<LINALG::matrix> an_;
        blaze::Band<LINALG::matrix> as_;
        LINALG::vector b_;

    public:
        linEqSystem( MESH::structured2dRegularRectangle const &mesh );

        const std::vector<int> getBands() const;
        const LINALG::matrix & getMatrix() const;
        const LINALG::vector & getSourceVector() const;
        void setDirectionalFlux( const GLOBAL::vector & ai, const CardinalDirection dir );
        void setConstVec( const GLOBAL::vector & b );
    };

    void solve(const linEqSystem & eqs,  GLOBAL::vector& X, std::string Method, GLOBAL::scalar tolerance, int maxIterations);


}