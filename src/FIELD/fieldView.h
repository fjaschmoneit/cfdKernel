#include "MESH/structured2d.h"
// #include "FIELD/field.h"

#include "globalTypeDefs.h"


// - FieldViewRange represents a logical subset (e.g. boundary or interior cells) of the mesh,
//   providing begin() and end() for iteration.
// - FieldViewIterator allows stepping over that subset, providing access and navigation
//   to individual field values in mesh order.
//
// Usage example:
//     for (auto& val : myField.boundary(0)) {
//         // val refers to the correct field value for boundary cell
//     }
//
//    for ( auto f = myField.internal().begin(); f < myField.internal().end(); ++f ) {
//
//    }
//

namespace FIELD {

    // Iterates over a (possibly discontinuous) subset of field values, defined by their mesh indices.
    // meshIt_ refers to an iterator over cell indices (not over all cells, but a subset, like a boundary or interior).
    // field_ points to the entire std::vector<float> representing the field data.
    // Dereferencing the iterator yields a reference to the relevant field value for the current mesh cell.
    class FieldViewIterator {
        // Underlying mesh iterator over a vector of ints (cell indices)
        // MESH::structured2dRegularRectangle::iterator meshIt_;
        // std::vector<unsigned int>::const_iterator meshIt_;
        // std::vector<unsigned int>::iterator meshIt_;
        MESH::Region::iterator meshIt_;

        // Pointer to the main field data vector. Used to map mesh index -> field value.
        GLOBAL::vector* field_;

    public:
        // necessary for std::range compatability
        using value_type = GLOBAL::scalar;
        using difference_type = std::ptrdiff_t;
        using reference = GLOBAL::scalar&;
        using pointer = GLOBAL::scalar*;
        using iterator_category = std::forward_iterator_tag;

        // constructors:
        FieldViewIterator(MESH::Region::iterator meshIt, GLOBAL::vector* fieldData)
            : meshIt_(meshIt), field_(fieldData) {}

        FieldViewIterator() : meshIt_{}, field_{nullptr} {}

        // public member functions:

        // Dereference: return the underlying field value at mesh's current cell index.
        GLOBAL::scalar& operator*() const {
            return (*field_)[*meshIt_];
        }

        // Pre-increment: move to the next mesh cell index in the mesh range.
        FieldViewIterator& operator++() {
            ++meshIt_;
            return *this;
        }

        // Post-increment:
        FieldViewIterator operator++(int) {
            auto tmp = *this;
            ++(*this);
            return tmp;
        }

        // Inequality: allows for-range and other iterator loops
        bool operator!=(const FieldViewIterator& other) const {
            return meshIt_ != other.meshIt_;
        }

        // Equality: not strictly needed, but generally good practice
        bool operator==(const FieldViewIterator& other) const {
            return meshIt_ == other.meshIt_;
        }

        pointer operator->() const {
            return &(**this);
        }

    };

    // View range class: represents a logical sub-range of field values, e.g. over a boundary or the interior.
    // Provides begin() and end() iterators that "see" the field as ordered by indices from the mesh's boundary or internal range.
    class FieldViewRange {
        const MESH::Region& meshRegion_;
        GLOBAL::vector* field_;

    public:
        FieldViewRange(const MESH::Region& meshRegion, std::vector<float>* fieldData)
            : meshRegion_(meshRegion), field_(fieldData) {}

        FieldViewIterator begin() const {
            return FieldViewIterator(meshRegion_.begin(), field_);
        }

        FieldViewIterator end() const {
            return FieldViewIterator(meshRegion_.end(), field_);
        }
    };




}
