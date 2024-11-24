#include <iostream>

#undef NIGEMIZU_USE_GUI_ASSERT

#include "meta/assert.h"

int main() {
    std::cout << "Assertion in CUI" << std::endl;
    NIGEMIZU_ASSERT(1 == 0);
    return 0;
}
