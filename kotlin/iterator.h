#ifndef KOTLIN_ITERATOR_H
#define KOTLIN_ITERATOR_H

#include "core.h"

namespace kt {
    template<typename T>
    class Iterator : public Any {
    protected:
        T _val;
    public:

        virtual T next() { return **this; };

        virtual Boolean hasNext() { return true; }

        T operator*() const { return _val; }
    };
}

#endif
