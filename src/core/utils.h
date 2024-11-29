#ifndef NIGEMIZU_CORE_UTILS_H_
#define NIGEMIZU_CORE_UTILS_H_

namespace nigemizu::core::utils {

class InitFlag {
public:
    InitFlag() : initialized_(false) {}

    explicit operator bool() const noexcept { return initialized_; }
    void Set() { initialized_ = true; }

private:
    bool initialized_;
};

}  // namespace nigemizu::core::utils

#endif  // NIGEMIZU_CORE_UTILS_H_
