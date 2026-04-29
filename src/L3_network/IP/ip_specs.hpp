#pragma once

// #include "../../common/common_net.hpp"
#include "../../L2_datalink/mac/mac_specs.hpp"
#include "../../common/generic_layers.hpp"
#include "../../common/misc.hpp"
#include <optional>

namespace cns = common_ns;

namespace ip_stack {

template <typename L2Type>
  requires cns::IsL2EntityType<L2Type>
class IpEntity {
public:
  using address_t = cns::IPv6Address;
  constexpr static cns::OsiLayer LAYER_IDX{cns::OsiLayer::NETWORK_IDX};

  IpEntity() = default;

  address_t const &getAddress() const;

  bool setL2Output(L2Type &l2_entity) {
    if (m_l2_output_ptr.has_value()) {
      return false;
    }
    m_l2_output_ptr = &l2_entity;
    return true;
  }

protected:
  address_t m_address{};
  std::optional<L2Type *> m_l2_output_ptr{};

private:
};

static_assert(cns::IsL3EntityType<IpEntity<MacEntity>>);

} // namespace ip_stack