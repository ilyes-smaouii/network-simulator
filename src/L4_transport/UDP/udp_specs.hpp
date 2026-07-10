#pragma once

#include "common/generic-layers.hpp"
#include "common/misc.hpp"

namespace cns = common_ns;

namespace ip_stack {

class UDPEntity {
public:
  using address_t = PortAddress;
  constexpr static cns::OsiLayer LAYER_IDX{cns::OsiLayer::TRANSPORT_IDX};

  UDPEntity();

  address_t const &getAddress() const;

protected:
private:
};

static_assert(cns::IsL4EntityType<UDPEntity>);

} // namespace ip_stack