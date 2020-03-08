#ifndef KOTLIN_MUTABLE_ITERATOR_H
#define KOTLIN_MUTABLE_ITERATOR_H

#include "core.h"

namespace kt {
    template<typename T>
    class MutableIterator : public Iterator<T> {
    public:
        // virtual void remove() = 0;
    };

    template<typename T>
    class ArrayList;

    template<typename T>
    class ArrayListIterator : public MutableIterator<T> {
        ArrayList<T> *_array = nullptr;
        Int _index = 0;
    protected:
        ArrayListIterator() = default;

    public:
        explicit ArrayListIterator(ArrayList<T> *array, Int index = 0) {
            this->_val = (_array = array)->get(_index = index);
        }

        Boolean operator==(const ArrayListIterator<T> &other) const {
            return _array == other._array && _index == other._index;
        }

        Boolean operator!=(const ArrayListIterator<T> &other) const {
            return _array != other._array || _index != other._index;
        }

        T next() override {
            Int index = _index;
            ++*this;
            return _array->get(index);
        }

        Boolean hasNext() override { return _index < _array->getSize(); }

        ArrayListIterator<T> &operator++() {
            this->_val = _array->get(++_index);
            return *this;
        }

        ArrayListIterator<T> operator++(int) {
            auto temp = *this;
            ++*this;
            return temp;
        }
    };

    template<typename T>
    struct LinkedListNode;

    template<typename T>
    class LinkedListIterator : public MutableIterator<T> {
        LinkedListNode<T> *_node;

    public:
        explicit LinkedListIterator(LinkedListNode<T> *node) : _node(node) {}

        T next() override {
            auto e = **this;
            ++*this;
            return e;
        };

        Boolean hasNext() override { return _node->_next != nullptr; }

        LinkedListIterator<T> &operator++() {
            _node = _node->_next;
            return *this;
        }

        LinkedListIterator<T> operator++(int) {
            auto temp = *this;
            ++*this;
            return temp;
        }

        Boolean operator==(const LinkedListIterator<T> &other) const {
            return _node == other._node;
        }

        Boolean operator!=(const LinkedListIterator<T> &other) const {
            return _node != other._node;
        }

        T operator*() const override { return _node->_item; }
    };
}

#endif
