#include <iostream>

#include "SDL2/SDL.h"

// DEBUG
#include "interfaces/boot.h"
#include "interfaces/framerate.h"
#include "interfaces/modal.h"
#include "models/timer.h"

int main(int argc, char* argv[]) {
    std::cout << "include SDL2 libraries" << std::endl;

    // DEBUG
    using nigemizu::interfaces::boot::InitGui;
    using nigemizu::interfaces::boot::CloseGui;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    std::cout << InitGui(window, renderer) << std::endl;

    using nigemizu::interfaces::framerate::FrameRateBalancer;
    int frame_rate = 60;
    FrameRateBalancer frb(frame_rate);

    using nigemizu::models::timer::SimpleTimer;
    SimpleTimer timer;

    int count = 0;
    int elapsed_frames = 0;

    frb.SetTimer();
    timer.Set();

    while (count < 5) {
        ++elapsed_frames;

        unsigned long long int elapsed_time = timer.GetElapsedTime();
        if (elapsed_time >= 1000) {
            std::cout << elapsed_time << " ms  ";
            std::cout << elapsed_frames << " frames" << std::endl;
            ++count;
            elapsed_frames = 0;
            timer.Set();
        }

        frb.Delay();
        frb.SetTimer();
    }

    CloseGui(window, renderer);

    return 0;
}
