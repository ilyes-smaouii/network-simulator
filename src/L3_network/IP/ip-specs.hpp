#pragma once

#include "cpp-common/logging.hpp"

// #include "../../common/common-net.hpp"
// #include "../../L2_datalink/mac/mac-specs.hpp"
#include "../../common/generic-layers.hpp"
#include "../../common/misc.hpp"
#include <type_traits>
#include <unordered_map>
#include <unordered_set>

namespace cns = common_ns;

namespace ip_stack {

// template <typename L2Type>
//   requires cns::IsL2EntityType<L2Type>
class IpEntityBase {
public:
  constexpr static cns::OsiLayer LAYER_IDX{cns::OsiLayer::NETWORK_IDX};
  using address_t = cns::IPv6Address;
  static_assert(HLP::Hashable<address_t>,
                "Error - address_t should be hashable !");
  using msg_t = std::string;

  IpEntityBase() = default;

  bool setAddress(address_t const &address);
  bool setAddress(address_t &&address);
  address_t const &getAddress() const;
  // TO-DO : figure out how I'll handle networks/neighbors
  auto const &getNeighbors() { return m_neighbors; }
  // auto const &getNeighbors() { return m_neighbors_addresses; }
  bool addNeighbor(const IpEntityBase &neighbor);
  bool removeNeighbor(const IpEntityBase &neighbor);
  bool addNeighbor(address_t const &neighbor_address);
  bool removeNeighbor(address_t const &neighbor_address);

  bool decapsulateMsg(const msg_t &msg);
  bool encapsulateMsg(const msg_t &msg, address_t const &destination);

  // bool setL2Output(L2Type &l2_entity) {
  //   if (m_l2_output_ptr.has_value()) {
  //     return false;
  //   }
  //   m_l2_output_ptr = &l2_entity;
  //   return true;
  // }

  // L2Type &getL2Output() {
  //   [[unlikely]] if (!m_l2_output_ptr.has_value()) {
  //     THROW_ERROR_MSG("L2 output not set for this IP entity");
  //   }
  //   return *m_l2_output_ptr.value();
  // }

  // L2Type const &getL2Output() const {
  //   [[unlikely]] if (!m_l2_output_ptr.has_value()) {
  //     THROW_ERROR_MSG("L2 output not set for this IP entity");
  //   }
  //   return *m_l2_output_ptr.value();
  // }

protected:
  bool m_can_set_address{false};
  address_t m_address{};
  std::unordered_map<address_t, const IpEntityBase *> m_neighbors{};
  std::unordered_set<address_t> m_neighbors_addresses{};
  // std::optional<L2Type *> m_l2_output_ptr{};

private:
};

static_assert(cns::IsL3EntityType<IpEntityBase>);

} // namespace ip_stack