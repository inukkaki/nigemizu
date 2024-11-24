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

    KeyConfig(
        impl::kbd::KeyCode transfer_up,
        impl::kbd::KeyCode transfer_left,
        impl::kbd::KeyCode transfer_right,
        impl::kbd::KeyCode transfer_down)
        : transfer_up(transfer_up),
          transfer_left(transfer_left),
          transfer_right(transfer_right),
          transfer_down(transfer_down) {}
    KeyConfig(const KeyConfig&) = default;
};

class Playable : public impl::eent::Entity {
public:
    explicit Playable(const KeyConfig& kc) : kc_(kc) {}
    virtual ~Playable() = default;

    void Control(const impl::kbd::Keyboard& kbd);

private:
    KeyConfig kc_;
};

}  // namespace nigemizu::entity::playable

#endif  // NIGEMIZU_ENTITY_PLAYABLE_H_
