#ifndef NIGEMIZU_MODELS_POOL_H_
#define NIGEMIZU_MODELS_POOL_H_

namespace nigemizu::models::pool {

namespace impl {

template <typename T>
concept Object = requires (T& x) {
    T();
};

}  // namespace impl

}  // namespace nigemizu::models::pool

#endif  // NIGEMIZU_MODELS_POOL_H_
