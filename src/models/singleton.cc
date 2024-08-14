#include "models/singleton.h"

#include <algorithm>
#include <functional>
#include <memory>
#include <mutex>
#include <utility>

namespace nigemizu::models::singleton {

namespace impl {

void SingletonFinalizer::AddFinalizer(std::function<void()>&& func) {
    finalizers_.emplace_back(std::forward<decltype(func)>(func));
}

void SingletonFinalizer::Finalize() {
    std::for_each(
        finalizers_.crbegin(),
        finalizers_.crend(),
        [](auto&& finalizer) -> void {
            finalizer();
        }
    ), finalizers_.clear();
}

template <typename T>
template <typename... Args>
T& SingletonImpl<T>::GetInstance(Args&&... args) {
    std::call_once(init_flag_, Create<Args...>, std::forward<Args>(args)...);
    return *instance_.get();
}

template <typename T>
template <typename... Args>
void SingletonImpl<T>::Create(Args&&... args) {
    instance_ = std::make_unique<T>(std::forward<Args>(args)...);
    SingletonFinalizer::AddFinalizer(
        []() -> void {
            instance_.reset(nullptr);
        }
    );
}

}  // namespace impl

// ...

}  // namespace nigemizu::models::singleton
