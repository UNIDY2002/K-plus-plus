#include "kotlin/all.h"

using namespace kt;

int main() {
    auto stack = Stack<Int>();
    stack.push(2);
    stack.push(3);
    stack.push(3);
    stack.pop();
    println(stack.peek());
    stack.push(6);
    println(stack);
    return 0;
}
