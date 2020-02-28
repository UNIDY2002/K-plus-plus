#ifndef KOTLIN_MUTABLE_ITERABLE_H
#define KOTLIN_MUTABLE_ITERABLE_H

#include "mutable_iterator.h"
#include "iterable.h"

namespace kt {
    template<typename T>
    class MutableIterable : public Iterable<T> {
    public:
        virtual Iterator<T> &iterator() = 0;
    };
}

#endif
