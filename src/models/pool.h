#ifndef NIGEMIZU_MODELS_POOL_H_
#define NIGEMIZU_MODELS_POOL_H_

#include <cassert>

namespace nigemizu::models::pool {

namespace impl {

template <typename T>
concept Object = requires (T& x) {
    T();
};

}  // namespace impl

template <impl::Object T>
class ObjectPool {
public:
    explicit ObjectPool(int size) : size_(size) {
        assert(size_ > 0);
        members_ = new T[size_];
    }
    virtual ~ObjectPool() {
        delete[] members_;
    }

protected:
    int size_;
    T* members_;
};

}  // namespace nigemizu::models::pool

#endif  // NIGEMIZU_MODELS_POOL_H_
