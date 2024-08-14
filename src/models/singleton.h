#ifndef NIGEMIZU_MODELS_SINGLETON_H_
#define NIGEMIZU_MODELS_SINGLETON_H_

#include <functional>
#include <memory>
#include <mutex>
#include <vector>

namespace nigemizu::models::singleton {

namespace impl {

class SingletonFinalizer final {
public:
    SingletonFinalizer() = delete;

    static void AddFinalizer(std::function<void()>&& func);
    static void Finalize();

private:
    static inline std::vector<std::function<void()>> finalizers_;
};

template <typename T>
class SingletonImpl final {
public:
    SingletonImpl() = delete;

    template <typename... Args>
    static T& GetInstance(Args&&... args);

private:
    template <typename... Args>
    static void Create(Args&&... args);

    static inline std::once_flag init_flag_;
    static inline std::unique_ptr<T> instance_;
};

}  // namespace impl

// ...

}  // namespace nigemizu::models::singleton

#endif  // NIGEMIZU_MODELS_SINGLETON_H_
