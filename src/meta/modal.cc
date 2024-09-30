#include "meta/modal.h"

#include <iostream>
#include <string>

#include "SDL2/SDL.h"

namespace nigemizu::meta::modal {

void ShowErrorMessage(const char* title, const char* message) {
    std::cerr << message << std::endl;
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, nullptr);
}

void ShowErrorMessage(
        const char* title, const char* message, const char* quotation) {
    std::string full_message = message;
    full_message.append("\n> ");
    full_message.append(quotation);
    std::cerr << full_message << std::endl;
    SDL_ShowSimpleMessageBox(
        SDL_MESSAGEBOX_ERROR, title, full_message.c_str(), nullptr);
}

}  // namespace nigemizu::meta::modal
