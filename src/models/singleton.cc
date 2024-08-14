#include "models/singleton.h"

#include <algorithm>
#include <functional>
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

}  // namespace impl

void Singleton::Finalize() {
    impl::SingletonFinalizer::Finalize();
}

}  // namespace nigemizu::models::singleton
