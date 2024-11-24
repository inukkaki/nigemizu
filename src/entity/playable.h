#ifndef NIGEMIZU_ENTITY_PLAYABLE_H_
#define NIGEMIZU_ENTITY_PLAYABLE_H_

#include <memory>

#include "entity/base.h"
#include "entity/delegate.h"
#include "entity/entity.h"
#include "interfaces/keyboard.h"

namespace nigemizu::entity::playable {

namespace impl {

namespace base = nigemizu::entity::base;
namespace dlgt = nigemizu::entity::delegate;
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
    Playable(
        const impl::base::PhysicalProperty& phys,
        std::unique_ptr<impl::dlgt::MoveDelegate>&& move,
        const KeyConfig& kc)
        : impl::eent::Entity(phys, std::move(move)),
          kc_(kc) {}
    virtual ~Playable() = default;

    virtual void Transfer(const impl::kbd::Keyboard& kbd);

    void Control(const impl::kbd::Keyboard& kbd);

private:
    KeyConfig kc_;
};

}  // namespace nigemizu::entity::playable

#endif  // NIGEMIZU_ENTITY_PLAYABLE_H_
