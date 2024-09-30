#include "core/singleton.h"

#include <algorithm>
#include <functional>
#include <utility>

namespace nigemizu::core::singleton {

namespace impl {

void SingletonFinalizer::AddFinalizer(std::function<void()>&& func) {
    // NOTE: This implement might occur errors when the function called by
    // several threads at the same time.
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

}  // namespace impl

void Singleton::Finalize() {
    impl::SingletonFinalizer::Finalize();
}

}  // namespace nigemizu::core::singleton
