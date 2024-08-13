#include "models/singleton.h"

#include <algorithm>
#include <functional>
#include <utility>
#include <vector>

namespace nigemizu::models::singleton {

namespace impl {

std::vector<std::function<void()>> SingletonFinalizer::finalizers_;

void SingletonFinalizer::AddFinalizer(std::function<void()>&& func) {
    finalizers_.emplace_back(std::forward<decltype(func)>(func));
}

void SingletonFinalizer::Finalize() {
    std::for_each(
        finalizers_.crbegin(),
        finalizers_.crend(),
        [](auto&& finalizer) {
            finalizer();
        }
    ), finalizers_.clear();
}

}  // namespace impl

// ...

}  // namespace nigemizu::models::singleton
