#pragma once

// #include "../../common/common_net.hpp"
#include "../../common/generic_layers.hpp"
#include "../../common/misc.hpp"

namespace cns = common_ns;

namespace ip_stack {

class MacEntity {
public:
  using address_t = cns::MacAddress;
  constexpr static cns::OsiLayer LAYER_IDX{cns::OsiLayer::DATALINK_IDX};

  MacEntity() = default;

  address_t const &getAddress() const;

protected:
  address_t m_address{};

private:
};

static_assert(cns::IsL2EntityType<MacEntity>);

} // namespace ip_stack