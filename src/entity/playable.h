#ifndef NIGEMIZU_ENTITY_PLAYABLE_H_
#define NIGEMIZU_ENTITY_PLAYABLE_H_

#include "entity/entity.h"
#include "interfaces/keyboard.h"

namespace nigemizu::entity::playable {

namespace impl {

namespace eent = nigemizu::entity::entity;
namespace kbd = nigemizu::interfaces::keyboard;

}  // namespace impl

struct KeyConfig {
    impl::kbd::KeyCode transfer_up;
    impl::kbd::KeyCode transfer_left;
    impl::kbd::KeyCode transfer_right;
    impl::kbd::KeyCode transfer_down;
};

class Playable : public impl::eent::Entity {
public:
    Playable() = default;
    virtual ~Playable() = default;
};

}  // namespace nigemizu::entity::playable

#endif  // NIGEMIZU_ENTITY_PLAYABLE_H_
