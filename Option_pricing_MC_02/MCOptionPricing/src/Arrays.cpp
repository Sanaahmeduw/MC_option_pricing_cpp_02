#include "Arrays.h"
#include <algorithm>
#include <cstddef>

MJArray::MJArray(unsigned long size)
    : Size(size), Capacity(size), Values(size > 0 ? new double[size] : nullptr) {}

MJArray::~MJArray() {
    if (Values != nullptr) {
        delete[] Values;
    }
}

MJArray::MJArray(const MJArray& original)
    : Size(original.Size), Capacity(original.Size), Values(new double[original.Size]) {
    std::copy(original.Values, original.Values + Size, Values);
}

MJArray& MJArray::operator=(const MJArray& original) {
    if (&original == this) {
        return *this;
    }

    if (original.Size > Capacity) {
        if (Values != nullptr) {
            delete[] Values;
        }
        Values = new double[original.Size];
        Capacity = original.Size;
    }

    Size = original.Size;
    std::copy(original.Values, original.Values + Size, Values);

    return *this;
}

void MJArray::resize(unsigned long newSize) {
    if (newSize > Capacity) {
        if (Values != nullptr) {
            delete[] Values;
        }
        Values = new double[newSize];
        Capacity = newSize;
    }
    Size = newSize;
}
