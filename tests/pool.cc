// Test for ObjectPool

#include <iostream>

#include "models/pool.h"

class A {
public:
    A() { std::cout << ++count_ << std::endl; }

private:
    inline static int count_ = 0;
};

class B {
public:
    B() = delete;
};

int main() {
    using nigemizu::models::pool::ObjectPool;

    ObjectPool<A> pool1(5);
    //ObjectPool<A> pool2(-5);  // Cause assertion

    //ObjectPool<B> pool3(5);  // Cause template constraint failure

    return 0;
}
