// Test for using DynamicPool with Singleton

#include <iostream>

#include "core/pool.h"
#include "core/utils.h"
#include "core/singleton.h"

class A {
public:
    A() = default;

    bool IsActivated() const { return true; }
    void Update() { /* NO-OP */ }
};

class B {
public:
    B() = default;

    bool IsActivated() const { return true; }
    void Update() { /* NO-OP */ }
};

int main() {
    using nigemizu::core::utils::InitFlag;
    using nigemizu::core::pool::DynamicPool;
    using nigemizu::core::singleton::Singleton;

    InitFlag f1;
    InitFlag f2;
    f2.Set();
    std::cout << "flag 1 : " << (f1 ? "T" : "F") << std::endl;
    std::cout << "flag 2 : " << (f2 ? "T" : "F") << std::endl;

    DynamicPool<A>& pa1 = Singleton::GetInstance<DynamicPool<A>>(5ull);
    DynamicPool<A>& pa2 = Singleton::GetInstance<DynamicPool<A>>();

    std::cout << (&pa1 == &pa2) << std::endl;

    DynamicPool<B>& pb1 = Singleton::GetInstance<DynamicPool<B>>();
        // Cause assertion here!
    DynamicPool<B>& pb2 = Singleton::GetInstance<DynamicPool<B>>(5ull);

    std::cout << (&pb1 == &pb2) << std::endl;

    return 0;
}
