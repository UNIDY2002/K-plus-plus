#ifndef KOTLIN_MUTABLE_COLLECTION_H
#define KOTLIN_MUTABLE_COLLECTION_H

#include "collection.h"
#include "mutable_iterable.h"

namespace kt {
    template<typename T>
    class MutableCollection : public Collection<T>, public MutableIterable<T> {
    public:
        virtual Iterator<T> &iterator() = 0;

        virtual Int add(T const &e) = 0;

        // virtual Boolean remove(T element) = 0;

        // virtual void clear() = 0;
    };
}

#endif
