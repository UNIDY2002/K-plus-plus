#ifndef KOTLIN_ITERABLE_H
#define KOTLIN_ITERABLE_H

#include "iterator.h"

namespace kt {
    template<typename T>
    class Iterable : public Any {
    public:
        virtual Iterator<T> &iterator() = 0;

        virtual void forEach(void action(T &)) = 0;
    };
}

#endif
