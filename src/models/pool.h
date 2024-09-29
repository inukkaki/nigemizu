#ifndef NIGEMIZU_MODELS_POOL_H_
#define NIGEMIZU_MODELS_POOL_H_

#include <cstddef>
#include <deque>
#include <memory>
#include <vector>

namespace nigemizu::models::pool {

namespace impl {

template <typename T>
concept Deactivatable = requires (T& x) {
    x.Activate();
    x.Deactivate();

    x.IsActivated();
};

}  // namespace impl

template <impl::Deactivatable T>
class ObjectPool {
public:
    explicit ObjectPool(size_t size)
        : size_(size), objects_(size_), buf_size_(size_) {}
    virtual ~ObjectPool() = default;

    std::shared_ptr<T> Create(std::unique_ptr<T>&& object) {
        std::shared_ptr<T> result;
        if (buf_.size() < buf_size_) {
            object->Activate();
            result = buf_.emplace_back(std::move(object));
        }
        return result;
    }

    void Update() {
        buf_size_ = 0ll;
        for (std::shared_ptr<T>& obj : objects_) {
            if (obj) {
                if (obj->IsActivated()) {
                    Process(*obj);
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

    size_t buf_size_;
    std::deque<std::shared_ptr<T>> buf_;

    virtual void Process(T& obj) const { /* NO-OP */ }
};

}  // namespace nigemizu::models::pool

#endif  // NIGEMIZU_MODELS_POOL_H_
