#include "models/config.h"

#include <cassert>

namespace nigemizu::models::config {

namespace {

float gWindowScale = kDefaultWindowScale;

int gWindowWidth = static_cast<int>(gWindowScale*kWindowBaseWidth);
int gWindowHeight = static_cast<int>(gWindowScale*kWindowBaseHeight);

int gFrameRate = kDefaultFrameRate;      // s-1
float gFrameDuration = 1.0f/gFrameRate;  // s

}  // namespace

float GetWindowScale() {
    return gWindowScale;
}

void SetWindowScale(float window_scale) {
    assert(window_scale > 0.0f);
    gWindowScale = window_scale;
    gWindowWidth = static_cast<int>(gWindowScale*kWindowBaseWidth);
    gWindowHeight = static_cast<int>(gWindowScale*kWindowBaseHeight);
}

int GetWindowWidth() {
    return gWindowWidth;
}

int GetWindowHeight() {
    return gWindowHeight;
}

int GetFrameRate() {
    return gFrameRate;
}

void SetFrameRate(int frame_rate) {
    assert(frame_rate > 0);
    gFrameRate = frame_rate;
    gFrameDuration = 1.0f/gFrameRate;
}

float GetFrameDuration() {
    return gFrameDuration;
}

}  // namespace nigemizu::models::config
