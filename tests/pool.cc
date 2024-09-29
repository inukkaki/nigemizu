// Test for ObjectPool

#include <iostream>
#include <memory>

#include "models/pool.h"

class A {
public:
    A() {}
};

int main() {
    using nigemizu::models::pool::ObjectPool;

    ObjectPool<A> pool(5);

    pool.PrintObjects();
    pool.PrintBuf();
    std::cout << std::endl;

    std::cout << pool.Create(std::make_unique<A>()) << std::endl;
    std::cout << std::endl;

    pool.PrintObjects();
    pool.PrintBuf();
    std::cout << std::endl;

    for (int i = 0; i < 5; ++i) {
        std::cout << pool.Create(std::make_unique<A>()) << std::endl;
    }
    std::cout << std::endl;

    pool.PrintObjects();
    pool.PrintBuf();
    std::cout << std::endl;

    return 0;
}
