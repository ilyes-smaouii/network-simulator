#pragma once

#include "cpp-common/common-base.hpp"
#include "cpp-common/logging.hpp"

// #include "../../common/common-net.hpp"
// #include "../../L2_datalink/mac/mac-specs.hpp"
#include "../../common/generic-layers.hpp"
#include "../../common/misc.hpp"
#include "../../common/ns-protocol.hpp"

#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace cns = common_ns;
namespace cns_p = cns::protocol;

namespace ip_stack {

// template <typename L2Type>
//   requires cns::IsL2EntityType<L2Type>
class IPv4EntityBase {
public:
  constexpr static cns::OsiLayer LAYER_IDX{cns::OsiLayer::NETWORK_IDX};
  using address_t = ip_stack::IPv4Address;
  using msg_t = std::vector<HLP::byte_t>;
  using subnet_mask_t = IPv4SubnetMask;

  static_assert(HLP::Hashable<address_t>,
                "Error - address_t should be hashable !");
  static_assert(cns_p::IsMsgType<msg_t>,
                "Error : msg_t doesn't satisfy IsMsgType requirements !");

  IPv4EntityBase() = default;
  IPv4EntityBase(address_t const &address);
  IPv4EntityBase(address_t &&address);

  address_t const &getAddress() const;
  bool setAddress(address_t const &address);
  bool setAddress(address_t &&address);
  bool setSubnetMask(subnet_mask_t const &subnet_mask);
  bool setSubnetMask(subnet_mask_t &&subnet_mask);
  // TO-DO : figure out how I'll handle networks/neighbors
  auto const &getNeighbors() { return m_neighbors; }
  // auto const &getNeighbors() { return m_neighbors_addresses; }
  bool addNeighbor(const IPv4EntityBase &neighbor);
  bool removeNeighbor(const IPv4EntityBase &neighbor);
  bool addNeighbor(address_t const &neighbor_address);
  bool removeNeighbor(address_t const &neighbor_address);

  bool decapsulateMsg(const msg_t &msg);
  bool encapsulateMsg(const msg_t &msg, address_t const &destination);

protected:
  bool m_can_set_address{false};
  bool m_can_set_subnet_mask{false};
  address_t m_address{};
  subnet_mask_t m_mask{};
  std::unordered_map<address_t, const IPv4EntityBase *> m_neighbors{};
  std::unordered_set<address_t> m_neighbors_addresses{};
  // std::optional<L2Type *> m_l2_output_ptr{};

private:
};

cns::protocol::Message IpMsgFromString(std::string const& msg_str);

static_assert(cns::IsL3EntityType<IPv4EntityBase>);

} // namespace ip_stack