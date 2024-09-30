// Test for Singleton

#include <iostream>

#include "core/singleton.h"

class A {
public:
    A() {
        i_ = 0;
        ++count_;
        std::cout << "A() called" << std::endl;
    }

    explicit A(int i) : i_(i) {
        ++count_;
        std::cout << "A(int) called" << std::endl;
    }

    ~A() {
        std::cout << "~A() called" << std::endl;
        std::cout << "  The constructor was called " << count_ << " times"
            << std::endl;
    }

    void Print(int some_value) {
        std::cout << "Received " << some_value << std::endl;
        std::cout << "i=" << i_ << ", count=" << count_ << std::endl;
    }

private:
    int i_;
    static inline int count_ = 0;
};

int main() {
    using nigemizu::core::singleton::Singleton;

    A& x = Singleton::GetInstance<A>(156);
    x.Print(9);

    A& y = Singleton::GetInstance<A>();
    y.Print(12);

    A& z = Singleton::GetInstance<A>(229);
    z.Print(11);

    Singleton::Finalize();

    return 0;
}
