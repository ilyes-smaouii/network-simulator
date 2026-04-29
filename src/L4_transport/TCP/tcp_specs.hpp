#pragma once

#include "../../common/common_net.hpp"
#include "../../common/generic_layers.hpp"
#include "../../common/misc.hpp"

namespace cns = common_ns;

namespace ip_stack {

class TCPEntity {
public:
  using address_t = cns::PortAddress;
  constexpr static cns::OsiLayer LAYER_IDX{cns::OsiLayer::TRANSPORT_IDX};
  constexpr static std::size_t MAX_PACKET_SIZE{
      65535}; // Maximum size of a TCP packet (including header and data)

  TCPEntity() = default;

  address_t const &getAddress() const;

protected:
  address_t m_address{};

private:
};

static_assert(cns::IsL4EntityType<TCPEntity>);

} // namespace ip_stack
