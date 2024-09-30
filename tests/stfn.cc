// Test for SingletonFinalizer

#include <iostream>

#include "core/singleton.h"

class A {
public:
    void DoSomething() const {
        std::cout << "Hello, this is A." << std::endl;
    }
};

class B {
public:
    void DoSomething() const {
        std::cout << "Hello, this is B." << std::endl;
    }
};

int main() {
    using nigemizu::core::singleton::impl::SingletonFinalizer;

    A a; a.DoSomething();
    B b; b.DoSomething();

    SingletonFinalizer::AddFinalizer([&a] { a.DoSomething(); });
    SingletonFinalizer::AddFinalizer([&b] { b.DoSomething(); });

    std::cout << "finalize..." << std::endl;

    SingletonFinalizer::Finalize();

    return 0;
}
