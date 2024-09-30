// Test for ObjectPool

#include <iostream>
#include <memory>

#include "core/pool.h"

int gDebugNum = -1;

void ChangeDebugNum(int num) {
    std::cout << "gDebugNum : " << gDebugNum << " -> ";
    gDebugNum = num;
    std::cout << gDebugNum << std::endl;
}

class A {
public:
    A(int num) : num_(num) {
        std::cout << "[" << num_ << "]" << std::endl;
    }

    void Activate() {
        std::cout << "[" << this << " Activated]" << std::endl;
    }

    void Deactivate() { /* NO-OP */ }

    bool IsActivated() const {
        bool result = true;
        if (gDebugNum == num_) { result = false; }
        return result;
    }

private:
    int num_;
};

int main() {
    using nigemizu::core::pool::ObjectPool;

    ObjectPool<A> pool(5);

    //pool.PrintObjects();
    //pool.PrintBuf();
    std::cout << std::endl;

    std::cout << pool.Create(std::make_unique<A>(0)) << std::endl;
    std::cout << std::endl;

    //pool.PrintObjects();
    //pool.PrintBuf();
    std::cout << std::endl;

    pool.Update();

    //pool.PrintObjects();
    //pool.PrintBuf();
    std::cout << std::endl;

    // ...

    for (int i = 0; i < 5; ++i) {
        std::cout << pool.Create(std::make_unique<A>(i + 1)) << std::endl;
    }
    std::cout << std::endl;

    //pool.PrintObjects();
    //pool.PrintBuf();
    std::cout << std::endl;

    // ...

    pool.Update();

    //pool.PrintObjects();
    //pool.PrintBuf();
    std::cout << std::endl;

    // ...

    pool.Update();

    //pool.PrintObjects();
    //pool.PrintBuf();
    std::cout << std::endl;

    // ...

    ChangeDebugNum(1);
    pool.Update();

    //pool.PrintObjects();
    //pool.PrintBuf();
    std::cout << std::endl;

    // ...

    for (int i = 0; i < 2; ++i) {
        std::cout << pool.Create(std::make_unique<A>(i + 1)) << std::endl;
    }
    std::cout << std::endl;

    //pool.PrintObjects();
    //pool.PrintBuf();
    std::cout << std::endl;

    ChangeDebugNum(3);
    pool.Update();

    //pool.PrintObjects();
    //pool.PrintBuf();
    std::cout << std::endl;

    return 0;
}
