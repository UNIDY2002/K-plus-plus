#ifndef KOTLIN_COLLECTION_H
#define KOTLIN_COLLECTION_H

#include "iterable.h"

namespace kt {
    template<typename T>
    class Collection : public Iterable<T> {
    public:
        virtual Int getSize() const = 0;

        virtual Boolean isEmpty() const = 0;

        Boolean isNotEmpty() const { return !isEmpty(); }

        virtual Boolean contains(T element) const = 0;

        virtual Iterator<T> &iterator() = 0;
    };
}

#endif
