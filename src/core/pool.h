#ifndef NIGEMIZU_CORE_POOL_H_
#define NIGEMIZU_CORE_POOL_H_

#include <cstddef>
#include <deque>
#include <memory>
#include <vector>

#include "meta/assert.h"

namespace nigemizu::core::pool {

namespace impl {

template <typename T, typename... Args>
concept Poolable = requires (T& x, Args&&... args) {
    x.IsActivated();

    x.Update(args...);
};

}  // namespace impl

template <impl::Poolable T>
class ObjectPool {
public:
    explicit ObjectPool(size_t size)
        : size_(size), objects_(size_), buf_size_(size_) {}
    virtual ~ObjectPool() = default;

    bool HasVacancy() const { return buf_.size() < buf_size_; }

    T& focus() const {
        NIGEMIZU_ASSERT(focus_);
        return *focus_;
    }

    std::shared_ptr<T> Create(std::unique_ptr<T>&& object) {
        std::shared_ptr<T> result;
        if (HasVacancy()) {
            result = buf_.emplace_back(std::move(object));
        }
        return result;
    }

    template <typename... Args>
    void Update(Args&&... args) {
        buf_size_ = 0ull;
        for (std::shared_ptr<T>& obj : objects_) {
            if (obj) {
                if (obj->IsActivated()) {
                    obj->Update(std::forward<Args>(args)...);
                } else {
                    obj.reset();
                }
            } else if (!buf_.empty()) {
                obj = buf_.front();
                buf_.pop_front();
            }
            if (!obj) { ++buf_size_; }
        }
    }

private:
    size_t size_;
    std::vector<std::shared_ptr<T>> objects_;
    std::shared_ptr<T> focus_;

    size_t buf_size_;
    std::deque<std::shared_ptr<T>> buf_;
};

}  // namespace nigemizu::core::pool

#endif  // NIGEMIZU_CORE_POOL_H_
