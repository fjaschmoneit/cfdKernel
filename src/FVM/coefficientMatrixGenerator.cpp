
#include "coefficientMatrixGenerator.h"

FVM::coefficientMatrixGenerator::coefficientMatrixGenerator(const MESH::structured2dRegularRectangle &mesh)
:pmesh_(std::make_shared<MESH::structured2dRegularRectangle>(mesh)),
 aw_(mesh.nbCells, 0.0),
 ae_(mesh.nbCells, 0.0),
 an_(mesh.nbCells, 0.0),
 as_(mesh.nbCells, 0.0),
 ap_(mesh.nbCells, 1.0),
 b_(mesh.nbCells, 1.0)
 {}

void FVM::coefficientMatrixGenerator::setConstVec( GLOBAL::vector & b ){
    for(auto i=0; i<b.size(); ++i){
        b_[i] = b[i];
    }
}

void FVM::coefficientMatrixGenerator::setDirectionalFlux( GLOBAL::vector & ai, CardinalDirection const dir  ){
    // this function takes a std vector and moves its content to a
    // directional blaze vector

    auto copyElements = [](LINALG::vector & newVec, GLOBAL::vector const & oldVec){
        for(auto i=0; i<oldVec.size(); ++i){
            newVec[i] = oldVec[i];
        }
    };

    if( dir == FVM::CardinalDirection::centre )    copyElements( ap_, ai );
    else if ( dir == FVM::CardinalDirection::west )    copyElements( aw_, ai );
    else if ( dir == FVM::CardinalDirection::east )    copyElements( ae_, ai );
    else if ( dir == FVM::CardinalDirection::north )    copyElements( an_, ai );
    else if ( dir == FVM::CardinalDirection::south )    copyElements( as_, ai );

}


void FVM::coefficientMatrixGenerator::assembleCoeffMatrix(LINALG::matrix &coefficientMatrix) {
    long nbCellsX = long(pmesh_->nbCellsX);

    LINALG::matrixOperations::fillBand(0, coefficientMatrix, ap_);
    LINALG::matrixOperations::fillBand(1, coefficientMatrix, ae_); // east band
    LINALG::matrixOperations::fillBand(-1, coefficientMatrix, aw_); // west band
    LINALG::matrixOperations::fillBand(nbCellsX, coefficientMatrix, as_); // south band
    LINALG::matrixOperations::fillBand(-nbCellsX, coefficientMatrix, an_); // north band
}

void FVM::coefficientMatrixGenerator::assembleConstVec( LINALG::vector & vec ){
    vec = std::move(b_);
}