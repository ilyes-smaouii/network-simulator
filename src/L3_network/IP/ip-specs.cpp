// #include "../../common/common-net.hpp"
// #include "../../common/generic-layers.hpp"
// #include "../../common/misc.hpp"

#include "ip-specs.hpp"
#include "../../L2_datalink/mac/mac-specs.hpp"
#include <utility>

namespace cns = common_ns;

namespace ip_stack {

bool IpEntityBase::setAddress(IpEntityBase::address_t const &address) {
  if (!m_can_set_address) {
    return false;
  }
  m_address = address;
  return true;
}

bool IpEntityBase::setAddress(IpEntityBase::address_t &&address) {
  if (!m_can_set_address) {
    return false;
  }
  m_address = std::move(address);
  return true;
}

bool IpEntityBase::addNeighbor(IpEntityBase const &neighbor) {
  return m_neighbors.insert(std::make_pair(neighbor.getAddress(), &neighbor))
      .second;
}

bool IpEntityBase::removeNeighbor(IpEntityBase const &neighbor) {
  return (m_neighbors.erase(neighbor.getAddress()) == 1);
}

bool IpEntityBase::addNeighbor(
    IpEntityBase::address_t const &neighbor_address) {
  return m_neighbors_addresses.insert(neighbor_address).second;
}

bool IpEntityBase::removeNeighbor(
    IpEntityBase::address_t const &neighbor_address) {
  return (m_neighbors_addresses.erase(neighbor_address) == 1);
}

} // namespace ip_stack