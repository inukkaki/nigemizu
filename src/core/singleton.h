#ifndef NIGEMIZU_CORE_SINGLETON_H_
#define NIGEMIZU_CORE_SINGLETON_H_

#include <functional>
#include <memory>
#include <mutex>
#include <utility>
#include <vector>

namespace nigemizu::core::singleton {

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
    static inline T& GetInstance(Args&&... args) {
        std::call_once(
            init_flag_, Create<Args...>, std::forward<Args>(args)...);
        return *instance_.get();
    }

private:
    template <typename... Args>
    static inline void Create(Args&&... args) {
        instance_ = std::make_unique<T>(std::forward<Args>(args)...);
        SingletonFinalizer::AddFinalizer(
            []() -> void {
                instance_.reset(nullptr);
            }
        );
    }

    static inline std::once_flag init_flag_;
    static inline std::unique_ptr<T> instance_;
};

}  // namespace impl

class Singleton final {
public:
    Singleton() = delete;

    template <typename T, typename... Args>
    static inline T& GetInstance(Args&&... args) {
        return impl::SingletonImpl<T>
            ::GetInstance(std::forward<Args>(args)...);
    }

    static void Finalize();
};

}  // namespace nigemizu::core::singleton

#endif  // NIGEMIZU_CORE_SINGLETON_H_
