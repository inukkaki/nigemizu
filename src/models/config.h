#ifndef NIGEMIZU_MODELS_CONFIG_H_
#define NIGEMIZU_MODELS_CONFIG_H_

namespace nigemizu::models::config {

inline constexpr char kTitle[] = "nigemizu (wip)";

inline constexpr float kDefaultWindowScale = 2.0f;

inline constexpr int kWindowBaseWidth = 480;
inline constexpr int kWindowBaseHeight = 320;

inline constexpr int kDefaultFrameRate = 60;  // s-1

float GetWindowScale();
void SetWindowScale(float window_scale);

int GetWindowWidth();
int GetWindowHeight();

int GetFrameRate();
void SetFrameRate(int frame_rate);

float GetFrameDuration();

}  // namespace nigemizu::models::config

#endif  // NIGEMIZU_MODELS_CONFIG_H_
