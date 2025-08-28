#include "gtest/gtest.h"
#include "FIELD/field.h"
#include "MESH/structured2d.h"
#include "FVM/linEqSystem.h"
#include "LINALG/linearEquationSolvers.h"

#include <iostream>
#include <ranges>


struct applicationFixture : public ::testing::Test {

};


// 2D Poisson Equation Test Case (Fitzpatrick Example)
//
// Problem Setup:
// - Domain: 0 ≤ x ≤ 1, 0 ≤ y ≤ 1 (rectangular)
// - PDE: ∇²φ = f(x,y)
// - Source term: f(x,y) = 6xy (1-y) - 2x^3
//
// Boundary Conditions:
// - Dirichlet: φ(x,0) = φ(x,1) = 0, φ(0,y) = 0,  φ(1,y) = y(1-y)
//
// Analytical Solution:
// φ(x,y) = y*(1-y)x^3
//
// Reference: R. Fitzpatrick, "An example solution of Poisson's equation in 2-d"
// https://farside.ph.utexas.edu/teaching/329/lectures/node71.html
TEST_F(applicationFixture, 2DPoissonDerichlet) {

    unsigned int res(10);

    // use uneven nb of cells in both directions, makes measuring along the center-lines easier
    const MESH::structured2dRegularRectangle mesh( 1., 5, 0.6, 3 );
    FVM::linEqSystem eqs { mesh };

    FIELD::field q(mesh);
    auto meshReciprocalSpacing = mesh.getCellReciprocalSpacing_X();

    // main diagonal
    std::ranges::fill( q.region(MESH::RegionID::Entire), -4.*meshReciprocalSpacing );
    std::ranges::for_each( q.region(MESH::RegionID::Boundary_left), [meshReciprocalSpacing](auto& q){ q += -1.*meshReciprocalSpacing; } );
    std::ranges::for_each( q.region(MESH::RegionID::Boundary_right), [meshReciprocalSpacing](auto& q){ q += -1.*meshReciprocalSpacing; } );
    std::ranges::for_each( q.region(MESH::RegionID::Boundary_top), [meshReciprocalSpacing](auto& q){ q += -1.*meshReciprocalSpacing; } );
    std::ranges::for_each( q.region(MESH::RegionID::Boundary_bottom), [meshReciprocalSpacing](auto& q){ q += -1.*meshReciprocalSpacing; } );
    eqs.setDirectionalFlux( q.getData(), FVM::CardinalDirection::centre );  // defined as a_p

    // west diagonal
    std::ranges::fill( q.region(MESH::RegionID::Entire), meshReciprocalSpacing );
    std::ranges::fill( q.region(MESH::RegionID::Boundary_left), 0. );
    eqs.setDirectionalFlux( q.getData(), FVM::CardinalDirection::west );

    // east diagonal
    std::ranges::fill( q.region(MESH::RegionID::Entire), meshReciprocalSpacing );
    std::ranges::fill( q.region(MESH::RegionID::Boundary_right), 0. );
    eqs.setDirectionalFlux( q.getData(), FVM::CardinalDirection::east );

    // south diagonal
    std::ranges::fill( q.region(MESH::RegionID::Entire), meshReciprocalSpacing );
    std::ranges::fill( q.region(MESH::RegionID::Boundary_bottom), 0. );
    eqs.setDirectionalFlux( q.getData(), FVM::CardinalDirection::south );

    // north diagonal
    std::ranges::fill( q.region(MESH::RegionID::Entire), meshReciprocalSpacing );
    std::ranges::fill( q.region(MESH::RegionID::Boundary_top), 0. );
    eqs.setDirectionalFlux( q.getData(), FVM::CardinalDirection::north );

    std::ranges::for_each( mesh.region(MESH::RegionID::Entire),
        [&](auto cellId) {
            auto x =  mesh.getCellCenterCoordinate_X(cellId);
            auto y = mesh.getCellCenterCoordinate_Y(cellId);

            // x^2 * ( 3/2 y^2 - y^3 ) - 1/2 x^4 y
            q[cellId] = x*x*(1.5*y*y - y*y*y) - 0.5 *x*x *x*x *y;
        } );

    GLOBAL::scalar bc_west(0.);
    GLOBAL::scalar bc_north(0.);
    GLOBAL::scalar bc_south(0.);

    std::ranges::for_each( q.region(MESH::RegionID::Boundary_left), [&](auto& g){ g += -2.*meshReciprocalSpacing*bc_west; } );
    std::ranges::for_each( q.region(MESH::RegionID::Boundary_top), [&](auto& g){ g += -2.*meshReciprocalSpacing*bc_north; } );
    std::ranges::for_each( q.region(MESH::RegionID::Boundary_bottom), [&](auto& g){ g += -2.*meshReciprocalSpacing*bc_south; } );

    // setting right bc to one for now:
    std::ranges::for_each( q.region(MESH::RegionID::Boundary_right), [&](auto& g){ g += -2.*meshReciprocalSpacing*0.0; } );

    // std::ranges::for_each( q.region(MESH::RegionID::Boundary_right),
    //     [&](auto& g) {
    //         auto y = mesh.getCellCenterCoordinate_Y(g);
    //         g += -2.*meshReciprocalSpacing* y*(1.-y)  ;
    //     } );

    eqs.setConstVec( q.getData() );
    //
    // std::ranges::for_each(q.region(MESH::RegionID::Entire), [](auto& q){std::cout<<q<<" ";} );
    // std::cout << std::endl;


    std::cout<<eqs.getMatrix()<<std::endl;

    GLOBAL::vector phi(mesh.nbCells(), 0.0);
    FVM::solve(eqs, phi, "gaussSeidel", 1e-4, 1e3);

    //
    GLOBAL::vector midX_sim(mesh.nbCellsY(), 0.0);
    GLOBAL::vector midX_thr(mesh.nbCellsY(), 0.0);

    for(int i = 0; i < mesh.nbCellsY(); ++i) {
        midX_sim[i] = phi[ mesh.nbCellsX()/2 + i*mesh.nbCellsX() ];

        auto x( 0.5*mesh.lenX() );
        auto y( (0.5 + static_cast<GLOBAL::scalar>(i))/meshReciprocalSpacing );
        // std::cout<<x<<" "<<y<<std::endl;
        midX_thr[i] = y*(1.-y)*x*x*x;
    }

    std::ranges::for_each(midX_sim, [&](auto& g) {std::cout << g << " "; });  std::cout << std::endl;
    std::ranges::for_each(midX_thr, [&](auto& g) {std::cout << g << " "; });  std::cout << std::endl;
    // φ(x,y) = y*(1-y)x^3

    GLOBAL::vector diff(mesh.nbCells(), 0.0);
    for (int i=0; i<mesh.nbCells(); ++i) {
        diff[i] = midX_thr[i] - midX_sim[i];
    }

    double max_norm = 0.0;
    for (double val : diff) {
        max_norm = std::max(max_norm, std::abs(val));
    }

    std::cout << max_norm << std::endl;
}


TEST_F(applicationFixture, oneDimensionalSteadyDiffusion) {
    // auto const mesh(MESH::structured2dRegularRectangle( 5.0, 2.0, 1 ));
    const MESH::structured2dRegularRectangle mesh( 5.0, 5, 2.0, 2 );

    FVM::linEqSystem eqs { mesh };
    // translating fluxes to coefficient arrays

    eqs.setDirectionalFlux( GLOBAL::vector{3,2,2,2,3,3,2,2,2,3}, FVM::CardinalDirection::centre );
    eqs.setDirectionalFlux( GLOBAL::vector{-1,-1,-1,-1,0,-1,-1,-1,-1,0}, FVM::CardinalDirection::east );
    eqs.setDirectionalFlux( GLOBAL::vector{0, -1,-1,-1,-1,0,-1,-1,-1,-1}, FVM::CardinalDirection::west );
    eqs.setConstVec( GLOBAL::vector{2*100,0,0,0,2*500,2*100,0,0,0,2*500} );

    // my unknown variable vector
    GLOBAL::vector T(mesh.nbCells(), 0.0);

    // make these enums for all available solvers
    std::string method("gaussSeidel");
    // make interface:  FVM::solve(T,method), i.e. T should know its eqs
    FVM::solve(eqs, T, method, 1e-4, 1e3);

    GLOBAL::vector solution{140, 220, 300, 380, 460, 140, 220, 300, 380, 460};

    for (int i=0; i< solution.size(); ++i) {
        EXPECT_NEAR( T[i], solution[i], 2e-4 );
    }
}
