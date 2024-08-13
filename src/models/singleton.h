#ifndef NIGEMIZU_MODELS_SINGLETON_H_
#define NIGEMIZU_MODELS_SINGLETON_H_

#include <functional>
#include <vector>

namespace nigemizu::models::singleton {

namespace impl {

class SingletonFinalizer final {
public:
    SingletonFinalizer() = delete;

    static void AddFinalizer(std::function<void()>&& func);
    static void Finalize();

private:
    static std::vector<std::function<void()>> finalizers_;
};

}  // namespace impl

// ...

}  // namespace nigemizu::models::singleton

#endif  // NIGEMIZU_MODELS_SINGLETON_H_
