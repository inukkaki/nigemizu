#include <iostream>

#include "SDL2/SDL.h"

// DEBUG
#include "interfaces/modal.h"

int main(int argc, char* argv[]) {
    std::cout << "include SDL2 libraries" << std::endl;

    // DEBUG
    using nigemizu::interfaces::modal::ShowErrorMessage;
    ShowErrorMessage("test", "test message");
    ShowErrorMessage("test", "test message", "test quotation");

    return 0;
}
