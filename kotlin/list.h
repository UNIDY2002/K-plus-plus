#ifndef KOTLIN_LIST_H
#define KOTLIN_LIST_H

#include <algorithm>
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

        void sort() {
            std::sort(_elem, _elem + _size);
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


    // LinkedList

    template<typename T>
    struct LinkedListNode {
        T _item;
        LinkedListNode *_prev;
        LinkedListNode *_next;

        LinkedListNode() = default;

        explicit LinkedListNode(T e, LinkedListNode *p = nullptr, LinkedListNode *s = nullptr)
                : _prev(p), _next(s) { _item = e; }

        LinkedListNode *insertAsPrev(T const &e) {
            auto x = new LinkedListNode(e, _prev, this);
            _prev->_next = x;
            _prev = x;
            return x;
        }

        LinkedListNode *insertAsNext(T const &e) {
            auto x = new LinkedListNode(e, _next, this);
            _next->_prev = x;
            _next = x;
            return x;
        }
    };

    template<typename T>
    class LinkedList : public MutableCollection<T> {
        Int _size{};
        LinkedListNode<T> *header, *trailer;

    protected:
        void init();

        Int clear();

        void copyNodes(LinkedListNode<T> *p, Int n);

    public:
        LinkedList() { init(); }

        ~LinkedList() {
            clear();
            delete header;
            delete trailer;
        }

        Iterator<T> &iterator() override;

        Int add(T const &e) override;

        Int getSize() const override;

        Boolean isEmpty() const override;

        Boolean contains(T element) const override;

        void forEach(void action(T &)) override;

        LinkedListNode<T> *first() const;

        LinkedListNode<T> *last() const;

        T &operator[](Int i) const;

        LinkedListNode<T> *find(T const &e, int n, LinkedListNode<T> *p) const;

        LinkedListNode<T> *find(T const &e, LinkedListNode<T> *p, int n) const;

        LinkedListNode<T> *linkFirst(T const &e);

        LinkedListNode<T> *linkLast(T const &e);

        LinkedListNode<T> *linkBefore(LinkedListNode<T> *p, T const &e);

        LinkedListNode<T> *linkAfter(LinkedListNode<T> *p, T const &e);

        T unlinkFirst();

        T unlinkLast();

        T unlink(LinkedListNode<T> *p);

        LinkedListIterator<T> &begin();

        LinkedListIterator<T> &end();

        String toString() const override;
    };

    template<typename T>
    void LinkedList<T>::init() {
        header = new LinkedListNode<T>;
        trailer = new LinkedListNode<T>;
        header->_next = trailer;
        header->_prev = nullptr;
        trailer->_prev = header;
        trailer->_next = nullptr;
        _size = 0;
    }

    template<typename T>
    Int LinkedList<T>::clear() {
        Int oldSize = _size;
        while (_size) unlinkFirst();
        return oldSize;
    }

    template<typename T>
    void LinkedList<T>::copyNodes(LinkedListNode<T> *p, Int n) {
        init();
        while (p != nullptr && n--) {
            linkLast(p->_item);
            p = p->_next;
        }
    }

    template<typename T>
    Iterator<T> &LinkedList<T>::iterator() {
        return *new LinkedListIterator<T>(header->_next);
    }

    template<typename T>
    Int LinkedList<T>::add(const T &e) {
        linkLast(e);
        return _size;
    }

    template<typename T>
    Int LinkedList<T>::getSize() const {
        return _size;
    }

    template<typename T>
    Boolean LinkedList<T>::isEmpty() const {
        return _size == 0;
    }

    template<typename T>
    Boolean LinkedList<T>::contains(T element) const {
        auto p = first();
        while (p->_next != nullptr) {
            if (p->_item == element) return true;
            p = p->_next;
        }
        return false;
    }

    template<typename T>
    void LinkedList<T>::forEach(void action(T &)) {
        auto p = first();
        while (p->_next != nullptr) {
            action(p->_item);
            p = p->_next;
        }
    }

    template<typename T>
    LinkedListNode<T> *LinkedList<T>::first() const { return header->_next; }

    template<typename T>
    LinkedListNode<T> *LinkedList<T>::last() const { return trailer->_prev; }

    template<typename T>
    T &LinkedList<T>::operator[](Int i) const {
        auto p = first();
        while (i--) p = p->_next;
        return p->_item;
    }

    template<typename T>
    LinkedListNode<T> *LinkedList<T>::find(const T &e, int n, LinkedListNode<T> *p) const {
        // TODO: null-safety!
        while (n--) if (e == (p = p->_prev)->_item) return p;
        return nullptr;
    }

    template<typename T>
    LinkedListNode<T> *LinkedList<T>::find(const T &e, LinkedListNode<T> *p, int n) const {
        // TODO: null-safety!
        while (n--) if (e == (p = p->_next)->_item) return p;
        return nullptr;
    }

    template<typename T>
    LinkedListNode<T> *LinkedList<T>::linkFirst(const T &e) { return linkAfter(header, e); }

    template<typename T>
    LinkedListNode<T> *LinkedList<T>::linkLast(const T &e) { return linkBefore(trailer, e); }

    template<typename T>
    LinkedListNode<T> *LinkedList<T>::linkBefore(LinkedListNode<T> *p, const T &e) {
        ++_size;
        return p->insertAsPrev(e);
    }

    template<typename T>
    LinkedListNode<T> *LinkedList<T>::linkAfter(LinkedListNode<T> *p, const T &e) {
        ++_size;
        return p->insertAsNext(e);
    }

    template<typename T>
    T LinkedList<T>::unlink(LinkedListNode<T> *p) {
        auto data = p->_item;
        p->_prev->_next = p->_next;
        p->_next->_prev = p->_prev;
        delete p;
        --_size;
        return data;
    }

    template<typename T>
    T LinkedList<T>::unlinkFirst() { return unlink(header->_next); }

    template<typename T>
    T LinkedList<T>::unlinkLast() { return unlink(trailer->_prev); }

    template<typename T>
    LinkedListIterator<T> &LinkedList<T>::begin() {
        return *new LinkedListIterator<T>(header->_next);
    }

    template<typename T>
    LinkedListIterator<T> &LinkedList<T>::end() {
        return *new LinkedListIterator<T>(trailer);
    }

    template<typename T>
    String LinkedList<T>::toString() const {
        String result = "[";
        auto p = first();
        while (p->_next != nullptr) {
            result += kToString(p->_item);
            if ((p = p->_next)->_next != nullptr) result += ", ";
        }
        result += ']';
        return result;
    }

    template<typename T>
    class Stack : public ArrayList<T> {
    public:
        Stack() = default;

        void push(const T &elem) {
            this->add(elem);
        }

        T &peek() {
            if (this->isEmpty()) throw std::exception();
            return this->get(this->getSize() - 1);
        }

        T &pop() {
            T &obj = peek();
            this->remove(this->getSize() - 1);
            return obj;
        }
    };
}

#endif