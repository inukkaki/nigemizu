#ifndef NIGEMIZU_MODELS_CONFIG_H_
#define NIGEMIZU_MODELS_CONFIG_H_

namespace nigemizu::models::config {

inline constexpr char kTitle[] = "nigemizu (wip)";

inline constexpr int kWindowWidth = 640;
inline constexpr int kWindowHeight = 480;

inline constexpr int kDefaultFrameRate = 60;  // s-1

int GetFrameRate();
void SetFrameRate(int frame_rate);

float GetFrameDuration();

}  // namespace nigemizu::models::config

#endif  // NIGEMIZU_MODELS_CONFIG_H_
