#include "kotlin/all.h"

using namespace kt;

int main() {
    auto list = MutableList<Int>(5, RIT(it * 2));
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
    return 0;
}
