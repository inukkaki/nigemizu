#include <iostream>

#include "SDL2/SDL.h"

// DEBUG
#include "interfaces/boot.h"
#include "interfaces/modal.h"

int main(int argc, char* argv[]) {
    std::cout << "include SDL2 libraries" << std::endl;

    // DEBUG
    using nigemizu::interfaces::boot::InitGui;
    using nigemizu::interfaces::boot::CloseGui;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    std::cout << InitGui(window, renderer) << std::endl;

    using nigemizu::interfaces::modal::ShowErrorMessage;
    ShowErrorMessage("test", "test message");
    ShowErrorMessage("test", "test message", "test quotation");

    CloseGui(window, renderer);

    return 0;
}
