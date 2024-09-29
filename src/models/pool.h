#ifndef NIGEMIZU_MODELS_POOL_H_
#define NIGEMIZU_MODELS_POOL_H_

#include <cstddef>
#include <memory>
#include <vector>

namespace nigemizu::models::pool {

template <typename T>
class ObjectPool {
public:
    explicit ObjectPool(size_t size) : size_(size), objects_(size_) {}
    virtual ~ObjectPool() = default;

private:
    size_t size_;
    std::vector<std::unique_ptr<T>> objects_;
};

}  // namespace nigemizu::models::pool

#endif  // NIGEMIZU_MODELS_POOL_H_
