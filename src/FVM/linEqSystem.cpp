#include "linEqSystem.h"


void FVM::solve(linEqSystem const& eqs,  GLOBAL::vector& X, std::string const Method, GLOBAL::scalar tolerance, int maxIterations ) {
    // i would prefer if X and X_blaze were sharing the same memory, making these two copy operations unneccessary.
    blaze::DynamicVector<GLOBAL::scalar> X_blaze(X.size());
    std::copy(X.begin(), X.end(), X_blaze.begin());

    if ( Method=="gaussSeidel" ){
        LINALG::linearEquationSolvers::solveGaussSeidel(
            eqs.getMatrix(),
            eqs.getBands(),
            eqs.getSourceVector(),
            X_blaze,
            maxIterations,
            tolerance);
    }

    std::copy(X_blaze.begin(), X_blaze.end(), X.begin());
}



// constructor
FVM::linEqSystem::linEqSystem(const MESH::structured2dRegularRectangle &mesh)
    :pmesh_(std::make_shared<MESH::structured2dRegularRectangle>(mesh)),
     A_(mesh.nbCells, mesh.nbCells),
     bands_(std::vector<int>{ static_cast<int>(-mesh.nbCellsX), -1, 0, 1, static_cast<int>(mesh.nbCellsX)} ),
     ap_(blaze::band(A_,0)),
     an_(blaze::band(A_,static_cast<int>(-mesh.nbCellsX))),
     ae_(blaze::band(A_,1)),
     as_(blaze::band(A_,static_cast<int>(mesh.nbCellsX))),
     aw_(blaze::band(A_,-1)),
     b_(mesh.nbCells, 0.0)
{
    // intializing coefficient matrix as idendity matrix, (I cannot use std::fill here)
    for(size_t i = 0; i < ap_.size(); i++)  ap_[i] = 1.;
    for(size_t i = 0; i < an_.size(); i++)  an_[i] = 0.;
    for(size_t i = 0; i < ae_.size(); i++)  ae_[i] = 0.;
    for(size_t i = 0; i < as_.size(); i++)  as_[i] = 0.;
    for(size_t i = 0; i < aw_.size(); i++)  aw_[i] = 0.;

    A_.shrinkToFit();
    b_.shrinkToFit();
    bands_.shrink_to_fit();
}

const std::vector<int> FVM::linEqSystem::getBands() const{
    return bands_;
}

const LINALG::matrix & FVM::linEqSystem::getMatrix() const {
    return A_;
}

const LINALG::vector & FVM::linEqSystem::getSourceVector() const {
    return b_;
}


void FVM::linEqSystem::setConstVec( const GLOBAL::vector & b ){
    for(auto i=0; i<b.size(); ++i){
        b_[i] = b[i];
    }
}

void FVM::linEqSystem::setDirectionalFlux( const GLOBAL::vector & ai, const CardinalDirection dir  ){

    if ( ai.size() != pmesh_->nbCells ) {
        throw std::runtime_error("Error in setDirectionalFlux: input vector should have dimension of nbCells.");
    }

    // this function takes a std vector and moves its content to a
    // directional blaze vector
    auto copyElements = [](blaze::Band<LINALG::matrix> & matrixBand, GLOBAL::vector const & fullVec, size_t first){
        for(auto i=0; i<matrixBand.size(); ++i){
            matrixBand[i] = fullVec[ i + first ];
        }
    };

    // cutting std::a_i to correct size in blaze::a_i, respecting lengths of off-diagonals
    if( dir == FVM::CardinalDirection::centre )    copyElements( ap_, ai, 0 );
    else if ( dir == FVM::CardinalDirection::east )    copyElements( ae_, ai, 0 );
    else if ( dir == FVM::CardinalDirection::south )    copyElements( as_, ai, 0 );
    else if ( dir == FVM::CardinalDirection::west )    copyElements( aw_, ai, 1 );
    else if ( dir == FVM::CardinalDirection::north )    copyElements( an_, ai, pmesh_->nbCellsX );
}