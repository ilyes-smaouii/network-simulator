// #include "../../common/common-net.hpp"
// #include "../../common/generic-layers.hpp"
// #include "../../common/misc.hpp"

#include "ip-specs.hpp"
#include "../../L2_datalink/mac/mac-specs.hpp"
#include <utility>

namespace cns = common_ns;

namespace ip_stack {

IPv4EntityBase::IPv4EntityBase(address_t const &address) {
  m_address = address;
}

IPv4EntityBase::IPv4EntityBase(address_t &&address) {
  m_address = std::move(address);
}

IPv4EntityBase::address_t const & IPv4EntityBase::getAddress() const {
  return m_address;
}

bool IPv4EntityBase::setAddress(IPv4EntityBase::address_t const &address) {
  if (!m_can_set_address) {
    return false;
  }
  m_address = address;
  return true;
}

bool IPv4EntityBase::setAddress(IPv4EntityBase::address_t &&address) {
  if (!m_can_set_address) {
    return false;
  }
  m_address = std::move(address);
  return true;
}

bool IPv4EntityBase::setSubnetMask(
    IPv4EntityBase::subnet_mask_t const &subnet_mask) {
  if (!m_can_set_subnet_mask) {
    return false;
  }
  m_mask = subnet_mask;
  return true;
}

bool IPv4EntityBase::setSubnetMask(
    IPv4EntityBase::subnet_mask_t &&subnet_mask) {
  if (!m_can_set_subnet_mask) {
    return false;
  }
  m_mask = std::move(subnet_mask);
  return true;
}

bool IPv4EntityBase::addNeighbor(IPv4EntityBase const &neighbor) {
  return m_neighbors.insert(std::make_pair(neighbor.getAddress(), &neighbor))
      .second;
}

bool IPv4EntityBase::removeNeighbor(IPv4EntityBase const &neighbor) {
  return (m_neighbors.erase(neighbor.getAddress()) == 1);
}

bool IPv4EntityBase::addNeighbor(
    IPv4EntityBase::address_t const &neighbor_address) {
  return m_neighbors_addresses.insert(neighbor_address).second;
}

bool IPv4EntityBase::removeNeighbor(
    IPv4EntityBase::address_t const &neighbor_address) {
  return (m_neighbors_addresses.erase(neighbor_address) == 1);
}

cns::protocol::Message IpMsgFromString(std::string const &msg_str) {
  // TO-DO : implement function
  return {};
}

} // namespace ip_stack