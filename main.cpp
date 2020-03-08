#include "kotlin/all.h"

using namespace kt;

int main() {
    auto list = LinkedList<Int>();
    list.add(2);
    list.add(3);
    list.add(3);
    list.add(6);
    list.add(7);
    list.add(8);
    println(list[4]);
    println(list);

    // iterator design pattern
    auto &iter = list.iterator();
    while (iter.hasNext()) print(iter.next());
    println();

    // range-based loop
    for (auto x:list) print(x);
    println();

    // forEach with lambda
    list.forEach(IT(print(it);));
    println();

    println(list.contains(3));
    println(list.contains(5));
    return 0;
}
