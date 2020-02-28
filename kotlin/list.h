#ifndef KOTLIN_LIST_H
#define KOTLIN_LIST_H

#include "mutable_collection.h"

namespace kt {

    // ArrayList

    template<typename T>
    class ArrayList : public MutableCollection<T> {
        const Int DEFAULT_CAPACITY{10};

        T *_elem{nullptr};
        Int _capacity{DEFAULT_CAPACITY};
        Int _size{0};

    protected:
        void copyFrom(const T *A, Int lo, Int hi) {
            _elem = new T[_capacity = (hi - lo) * 2];
            _size = 0;
            while (lo < hi) _elem[_size++] = A[lo++];
        }

        void expand() {
            if (_size >= _capacity) {
                T *old = _elem;
                _elem = new T[_capacity = _capacity * 2];
                for (Int i = 0; i < _size; ++i) _elem[i] = old[i];
                delete[] old;
            }
        }

    public:

        // basics

        ArrayList() { _elem = new T[_capacity]; }

        ~ArrayList() { delete[] _elem; }

        explicit ArrayList(const Int &c) { _elem = new T[_capacity = c]; }

        ArrayList(const ArrayList<T> &A) { copyFrom(A._elem, 0, A._size); }

        ArrayList(const ArrayList<T> &A, Int &lo, Int &hi) { copyFrom(A._elem, lo, hi); }

        ArrayList<T> &operator=(const ArrayList<T> &A) {
            if (this != &A) {
                if (_elem) delete[] _elem;
                copyFrom(A._elem, 0, A._size);
            }
            return *this;
        }

        T &operator[](Int i) const { return _elem[i]; }

        T &get(Int i) const { return _elem[i]; }

        // consts

        Int getSize() const override { return _size; }

        Boolean isEmpty() const override { return _size == 0; }

        Boolean contains(T element) const override {
            for (Int i = 0; i < _size; ++i) if (element == _elem[i]) return true;
            return false;
        }

        // writable

        Int remove(Int lo, Int hi) {
            if (lo == hi) return 0;
            while (hi < _size) _elem[lo++] = _elem[hi++];
            _size = lo;
            return hi - lo;
        }

        T remove(Int index) {
            T e = _elem[index];
            remove(index, index + 1);
            return e;
        }

        Int insert(Int index, T const &e) {
            expand();
            for (Int i = _size; i > index; --i) _elem[i] = _elem[i - 1];
            _elem[index] = e;
            ++_size;
            return index;
        }

        Int insert(T const &e) { return insert(_size, e); }

        Int add(T const &e) override { return insert(_size, e); }

        // overrides

        String toString() const override {
            String result = "[";
            for (int i = 0; i < this->getSize(); ++i) {
                result += kToString(this->get(i));
                if (i < this->getSize() - 1) result += ", ";
            }
            result += ']';
            return result;
        }

        Boolean operator==(const ArrayList<T> &A) {
            for (int i = 0; i < this->getSize(); ++i) {
                if (this->get(i) != A.get(i)) return false;
            }
            return true;
        }

        void forEach(void action(T &)) {
            for (Int i = 0; i < _size; ++i) action(_elem[i]);
        }

        // iterator

        Iterator<T> &iterator() override {
            return *new ArrayListIterator<T>(this);
        }

        ArrayListIterator<T> &aIterator() {
            return *new ArrayListIterator<T>(this);
        }

        ArrayListIterator<T> &begin() {
            return *new ArrayListIterator<T>(this);
        }

        ArrayListIterator<T> &end() {
            return *new ArrayListIterator<T>(this, _size);
        }

    };


    // MutableList

    template<typename T>
    class MutableList : public ArrayList<T> {
    public:
        MutableList() = default;

        MutableList(Int size, T init(Int &)) {
            for (Int i = 0; i < size; ++i) this->insert(init(i));
        }
    };

    template<typename T>
    void parseArgs(MutableList<T> &) {}

    template<typename T, typename... Args>
    void parseArgs(MutableList<T> &list, T head, Args... rest) {
        list.insert(head);
        parseArgs<T>(list, rest...);
    }

    template<typename T>
    MutableList<T> mutableListOf() { return MutableList<T>(); }

    template<typename T, typename... Args>
    MutableList<T> mutableListOf(T &value) {
        auto list = MutableList<T>();
        list.insert(value);
        return list;
    }

    template<typename T, typename... Args>
    MutableList<T> mutableListOf(T head, Args... rest) {
        MutableList<T> list;
        parseArgs(list, head, rest...);
        return list;
    }
}

#endif