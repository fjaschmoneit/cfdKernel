
// #ifndef TESTING_STRUCTURED2D_H
// #define TESTING_STRUCTURED2D_H
//
// #endif //TESTING_STRUCTURED2D_H
//
// // I only want to generate one mesh.
#pragma once


//#include <cstddef>
#include <vector>
#include <stdexcept>
#include <unordered_map>


namespace MESH {

    // Enum for region identifiers
    enum class RegionID {
        Internal,
        Boundary_left,
        Boundary_bottom,
        Boundary_right,
        Boundary_top
    };

    struct region {
        std::vector<unsigned int> cells;
        std::vector<unsigned int>::const_iterator begin() const { return cells.begin(); }
        std::vector<unsigned int>::const_iterator end() const { return cells.end(); }// past-last-element iterator cannot be dereferenced
        std::vector<unsigned int>::const_iterator last() const { return std::prev(cells.end()); } // iterator to last existing element, can be dereferenced.
    };

    class structured2dRegularRectangle{

    private:
        // Registry of all regions; enum class ensures type safety
        std::unordered_map<RegionID, region> regions;

        // how can I do this at compile time?
        // Each boundary side is represented by a vector of cell indices
        // example: rectangular mesh with (nbX,nbY)=(5,4) cells
        // its cell and boundary indices are illustrated here:
        //
        //               3
        //     +----+----+----+----+----+
        //     |  0 |  1 |  2 |  3 |  4 |
        //     +----+----+----+----+----+
        //     |  5 |  6 |  7 |  8 |  9 |
        //  0  +----+----+----+----+----+    2
        //     | 10 | 11 | 12 | 13 | 14 |
        //     +----+----+----+----+----+
        //     | 15 | 16 | 17 | 18 | 19 |
        //     +----+----+----+----+----+
        //               1
        //
        // the boundaries are names counter-clockwise, starting with the left one.
        // the cell ids per boundary also follow a counter-clockwise direction.
        // boundaries[0] = [0,5,10,15]
        // boundaries[1] = [15,16,17,18,19]
        // boundaries[2] = [19,14,9,4]
        // boundaries[3] = [4,3,2,1,0]

        void fillBoundaries();
        void fillInternalCells();

        bool isBoundaryCell( unsigned int i ) const;

    public:

        // order must follow initialization list
        const float lenX, lenY;
        const unsigned int cellsPerLength, nbCellsX, nbCellsY, nbCells;

        structured2dRegularRectangle(float lengthX, float lengthY, int cellsPerMeter);
        // ~structured2dRegularRectangle() override = default;

        // // Example: add region (could be called during construction or mesh setup)
        // void addRegion(RegionID id, std::vector<unsigned int> cellIndices) {
        //     regions[id] = region{std::move(cellIndices)};
        // }

        // Accessor: returns const reference for safe, read-only iteration
        const region& getRegion(RegionID id) const {
            auto it = regions.find(id);
            if (it == regions.end()) throw std::out_of_range("Unknown region id");
            return it->second;
        }
    };

}