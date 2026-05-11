#include <bit>
#include <concepts>
#include <cstdint>
#include <cstring>
#include <initializer_list>
#include <stdexcept>
#include <string>

// TO-DO: improve includes
#include "../../lib/cpp-common/logging.hpp"

#include "common-net.hpp"
#include "misc.hpp"

namespace ip_stack {

// IPv4SubnetMask

bool IPv4SubnetMask::isValid() const { return isValidSubnetMask(*this); }

IPv4SubnetMask::mask_t IPv4SubnetMask::toMask() const { return m_mask; }

std::size_t IPv4SubnetMask::getLength() const { return std::popcount(m_mask); }

// IPv4

IPv4Address::IPv4Address(IPv4Address::underlying_address_t const &addr)
    : m_address(addr) {}

// IPv4Address::IPv4Address(std::initializer_list<octet_t> init) {
//   std::copy_n(init.begin(), std::min(init.size(), OCTET_COUNT),
//               m_address.begin());
// }

IPv4Address::IPv4Address(IPv4Address::octet_t const &a,
                         IPv4Address::octet_t const &b,
                         IPv4Address::octet_t const &c,
                         IPv4Address::octet_t const &d) {
  m_address = {a, b, c, d};
}

IPv4Address::octet_t *IPv4Address::data() { return m_address.data(); }

const IPv4Address::octet_t *IPv4Address::data() const {
  return m_address.data();
}

IPv4Address::octet_t const &IPv4Address::operator[](std::size_t index) const {
  return m_address.at(index);
}

IPv4Address::octet_t const &IPv4Address::at(std::size_t index) const {
  return m_address.at(index);
}

std::string IPv4Address::toString() const {
  return std::to_string(m_address.at(0)) + "." +
         std::to_string(m_address.at(1)) + "." +
         std::to_string(m_address.at(2)) + "." +
         std::to_string(m_address.at(3));
}

// IPv6

IPv6Address::IPv6Address(const std::array<cns::byte_t, OCTET_COUNT> &addr)
    : m_address(addr) {}

IPv6Address::IPv6Address(std::initializer_list<cns::byte_t> init) {
  std::copy_n(init.begin(), std::min(init.size(), OCTET_COUNT),
              m_address.begin());
}

IPv6Address::IPv6Address(IPv4Address const &ipv4_addr) {
  // Map the IPv4 address to an IPv6 address using the IPv4-mapped IPv6 address
  // format
  m_address.at(0) = 0;
  m_address.at(1) = 0;
  m_address.at(2) = 0;
  m_address.at(3) = 0;
  m_address.at(4) = 0;
  m_address.at(5) = 0;
  m_address.at(6) = 0;
  m_address.at(7) = 0;
  m_address.at(8) = 0;
  m_address.at(9) = 0;
  m_address.at(10) = 0xFF; // FF in hexadecimal
  m_address.at(11) = 0xFF; // FF in hexadecimal
  static_assert(std::convertible_to<decltype(ipv4_addr.data()),
                                    const IPv4Address::octet_t *>,
                "Error : expected IPv4Address::data() to yield pointer to "
                "IPv4Address::octet_t !");
  std::copy_n(ipv4_addr.data(), IPv4Address::OCTET_COUNT,
              m_address.data() + 12);
}

IPv6Address::IPv6Address(IPv4Address &&ipv4_addr) {
  // Map the IPv4 address to an IPv6 address using the IPv4-mapped IPv6 address
  // format
  m_address.at(0) = 0;
  m_address.at(1) = 0;
  m_address.at(2) = 0;
  m_address.at(3) = 0;
  m_address.at(4) = 0;
  m_address.at(5) = 0;
  m_address.at(6) = 0;
  m_address.at(7) = 0;
  m_address.at(8) = 0;
  m_address.at(9) = 0;
  m_address.at(10) = 0xFF; // FF in hexadecimal
  m_address.at(11) = 0xFF; // FF in hexadecimal
  static_assert(std::convertible_to<decltype(ipv4_addr.data()),
                                    const IPv4Address::octet_t *>,
                "Error : expected IPv4Address::data() to yield pointer to "
                "IPv4Address::octet_t !");
  std::copy_n(ipv4_addr.data(), IPv4Address::OCTET_COUNT,
              m_address.data() + 12);
}

IPv6Address::octet_t *IPv6Address::data() { return m_address.data(); }

const IPv6Address::octet_t *IPv6Address::data() const {
  return m_address.data();
}

IPv6Address::octet_t const &IPv6Address::operator[](std::size_t index) const {
  return m_address.at(index);
}

IPv6Address::octet_t const &IPv6Address::at(std::size_t index) const {
  return m_address.at(index);
}

bool IPv6Address::isIPv4() const {
  // Check if the first 10 bytes are 0 and the next 2 bytes are 0xFF
  return std::memcmp(m_address.data(),
                     "\x00\x00\x00\x00\x00\x00\x00\x00\xFF\xFF\xFF\xFF",
                     12) == 0;
}

IPv4Address IPv6Address::toIPv4() const {
  if (!isIPv4()) {
    throw std::runtime_error(
        "Cannot convert to IPv4: Not an IPv4-mapped IPv6 address");
  }
  return IPv4Address{std::array<cns::byte_t, IPv4Address::OCTET_COUNT>{
      m_address.at(12), m_address.at(13), m_address.at(14), m_address.at(15)}};
}

std::string IPv6Address::toString() const {
  std::string result;
  result.reserve(
      8 * 5); // Each group of 2 bytes can be represented as 4 hex digits + ':'

  const std::uint16_t *data =
      reinterpret_cast<const std::uint16_t *>(m_address.data());
  for (std::size_t i = 0; i < OCTET_COUNT / 2; ++i) {
    HLP::Log::quickHexToString<std::uint16_t>(data[i], result.data() + i * 5);
    result[i * 5 + 4] = ':';
  }
  result[39] = '\0';
  return result;
}

PortAddress::PortAddress(PortAddress::underlying_address_t const &port_number)
    : m_port_number(port_number) {}

PortAddress::PortAddress(PortAddress::underlying_address_t &&port_number)
    : m_port_number(std::move(port_number)) {}

} // namespace ip_stack