#include "models/config.h"

namespace nigemizu::models::config {

namespace {

int gFrameRate = kDefaultFrameRate;      // s-1
float gFrameDuration = 1.0f/gFrameRate;  // s

}  // namespace

int GetFrameRate() {
    return gFrameRate;
}

void SetFrameRate(int frame_rate) {
    gFrameRate = frame_rate;
    gFrameDuration = 1.0f/gFrameRate;
}

float GetFrameDuration() {
    return gFrameDuration;
}

}  // namespace nigemizu::models::config
