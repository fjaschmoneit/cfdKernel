#include <iostream>
#include <blaze/Forward.h>
#include <blaze/Math.h>

#include "LINALG/linearEquationSolvers.h"
#include "LINALG/matrixOperations.h"
#include "FVM/collocatedField.h"
#include "MESH/structured2d.h"
#include "FIELD/field.h"

using vector = blaze::DynamicVector<double, blaze::columnVector>;
using matrix = blaze::CompressedMatrix<double, blaze::rowMajor>;


int main()
{


//    std::vector<double> d1{ 0.0, 5.0, 1.0, 3.0 };
//    std::experimental::mdspan field( d1.data(), std::experimental::extents{2,2} );
//    std::cout << field(1,1) << std::endl;
//
//    std::vector<double> d{
//            0, 5, 1, 3, 8,
//            4, 2, 7, 6, 2
//    };
//    field = std::experimental::mdspan( d.data(), std::experimental::extents{2,5} );
//    std::cout << field(1,3) << std::endl;


    auto mesh(std::make_shared<MESH::structured2dRegularRectangle>( 3.0, 2.0, 1 ));
    auto T = FIELD::field( mesh );



//    auto T = FVM::collocatedField( mesh );
//    std::cout << T.field(0,1) << std::endl;

    const size_t NN(mesh->nbCells);

    matrix A = LINALG::matrixOperations::newIdentityMatrix(NN);
    std::cout << A << std::endl;

    vector ap( NN, 0.0 );
    for (size_t i =0; i< ap.size(); ++i){
        ap[i] = i+1;
    }

    LINALG::matrixOperations::fillBand(0, A, ap); // central band
    LINALG::matrixOperations::fillBand(1, A, ap); // east band
    LINALG::matrixOperations::fillBand(-1, A, ap); // west band

    LINALG::matrixOperations::fillBand(-4, A, ap); // north band
    LINALG::matrixOperations::fillBand(4, A, ap); // south band


    std::cout<< A << std::endl;

    blaze::DynamicVector<double,blaze::columnVector> x( NN, 0.1 ), b( NN, 1.0 );

//    blaze::DynamicVector<double,blaze::columnVector> x,b;

//            vector1.insert( vector1.end(), vector2.begin(), vector2.end() );


    LINALG::linearEquationSolvers::solveConjugateGradient(A, b, x, 1e2, 1e-5);

    std::cout << x << std::endl;

    return 0;
}

