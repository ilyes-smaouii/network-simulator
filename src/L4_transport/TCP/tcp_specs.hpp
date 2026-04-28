#include "../../common/generic_layers.hpp"

namespace cns = common_ns;

class TCPEntity : public cns::GenericL4Entity {
public:
  using GenericL4Entity::address_t;
  using GenericL4Entity::LAYER_IDX;

  TCPEntity();

  address_t const &getAddress() const override;

protected:
  address_t _address{};

private:
};

static_assert(cns::IsAddressableEntity<TCPEntity>);