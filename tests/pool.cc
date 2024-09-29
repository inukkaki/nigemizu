// Test for ObjectPool

#include <iostream>

#include "models/pool.h"

class A {
public:
    A() {}
};

int main() {
    using nigemizu::models::pool::ObjectPool;

    ObjectPool<A> pool(10);

    return 0;
}
