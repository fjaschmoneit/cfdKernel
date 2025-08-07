#include "gtest/gtest.h"
#include "FIELD/field.h"
#include "MESH/structured2d.h"
#include "FVM/linEqSystem.h"
#include "LINALG/linearEquationSolvers.h"


struct applicationFixture : public ::testing::Test {

};


TEST_F(applicationFixture, 2DPoissonProblem) {
    // auto const mesh(MESH::structured2dRegularRectangle( 4.0, 4.0, 1 ));
    const MESH::structured2dRegularRectangle mesh( 4.0, 4.0, 1 );
    FVM::linEqSystem eqs { mesh };

    GLOBAL::vector ap(mesh.nbCells);
}


TEST_F(applicationFixture, oneDimensionalSteadyDiffusion) {
    // auto const mesh(MESH::structured2dRegularRectangle( 5.0, 2.0, 1 ));
    const MESH::structured2dRegularRectangle mesh( 5.0, 2.0, 1 );

    FVM::linEqSystem eqs { mesh };
    // translating fluxes to coefficient arrays
    eqs.setDirectionalFlux( GLOBAL::vector{3,2,2,2,3,3,2,2,2,3}, FVM::CardinalDirection::centre );
    eqs.setDirectionalFlux( GLOBAL::vector{-1,-1,-1,-1,0,-1,-1,-1,-1,0}, FVM::CardinalDirection::east );
    eqs.setDirectionalFlux( GLOBAL::vector{0, -1,-1,-1,-1,0,-1,-1,-1,-1}, FVM::CardinalDirection::west );
    eqs.setConstVec( GLOBAL::vector{2*100,0,0,0,2*500,2*100,0,0,0,2*500} );

    // my unknown variable vector
    GLOBAL::vector T(mesh.nbCells, 0.0);

    std::string method("gaussSeidel");
    // make interface:  FVM::solve(T,method), i.e. T should know its eqs
    FVM::solve(eqs, T, method, 1e-4, 1e3);

    GLOBAL::vector solution{140, 220, 300, 380, 460, 140, 220, 300, 380, 460};

    for (int i=0; i< solution.size(); ++i) {
        EXPECT_NEAR( T[i], solution[i], 2e-4 );
    }
}
