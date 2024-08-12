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
    FrameRateBalancer frb(60);

    using nigemizu::interfaces::framerate::FrameRateMeasurer;
    FrameRateMeasurer frm;
    double measured_frame_rate = 0.0;

    using nigemizu::models::timer::SimpleTimer;
    SimpleTimer timer;

    int count = 0;

    frb.SetTimer();
    frm.SetTimer();
    timer.Set();

    while (count < 5) {
        unsigned long long int elapsed_time = timer.GetElapsedTime();
        if (elapsed_time >= 1000) {
            std::cout << "  " << elapsed_time << " ms" << std::endl;
            ++count;
            timer.Set();

            if (count == 2) {
                frb.SetFrameRate(30);
            }
        }

        // Measure the frame rate
        if (frm.MeasureFrameRate(measured_frame_rate)) {
            std::cout << measured_frame_rate << " fps" << std::endl;
        }

        frb.Balance();
    }

    CloseGui(window, renderer);

    return 0;
}
