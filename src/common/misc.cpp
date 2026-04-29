#include <cstdint>
#include <cstring>
#include <initializer_list>
#include <stdexcept>
#include <string>

// TO-DO: improve includes
#include "../../lib/cpp-common/logging.hpp"

#include "common_net.hpp"
#include "misc.hpp"

namespace common_ns {

// IPv4

IPv4Address::IPv4Address(const std::array<cns::byte_t, OCTET_COUNT> &addr)
    : _address(addr) {}

IPv4Address::IPv4Address(std::initializer_list<cns::byte_t> init) {
  std::copy_n(init.begin(), std::min(init.size(), OCTET_COUNT),
              _address.begin());
}

IPv4Address::octet_t *IPv4Address::data() { return _address.data(); }

const IPv4Address::octet_t *IPv4Address::data() const {
  return _address.data();
}

IPv4Address::octet_t const &IPv4Address::operator[](std::size_t index) const {
  return _address.at(index);
}

IPv4Address::octet_t const &IPv4Address::at(std::size_t index) const {
  return _address.at(index);
}

std::string IPv4Address::toString() const {
  return std::to_string(_address.at(0)) + "." + std::to_string(_address.at(1)) +
         "." + std::to_string(_address.at(2)) + "." +
         std::to_string(_address.at(3));
}

// IPv6

IPv6Address::IPv6Address(const std::array<cns::byte_t, OCTET_COUNT> &addr)
    : _address(addr) {}

IPv6Address::IPv6Address(std::initializer_list<cns::byte_t> init) {
  std::copy_n(init.begin(), std::min(init.size(), OCTET_COUNT),
              _address.begin());
}

IPv6Address::IPv6Address(const IPv4Address &ipv4_addr) {
  // Map the IPv4 address to an IPv6 address using the IPv4-mapped IPv6 address
  // format
  _address.at(0) = 0;
  _address.at(1) = 0;
  _address.at(2) = 0;
  _address.at(3) = 0;
  _address.at(4) = 0;
  _address.at(5) = 0;
  _address.at(6) = 0;
  _address.at(7) = 0;
  _address.at(8) = 0;
  _address.at(9) = 0;
  _address.at(10) = 0xFF; // FF in hexadecimal
  _address.at(11) = 0xFF; // FF in hexadecimal
  std::copy_n(ipv4_addr.data(), IPv4Address::OCTET_COUNT, _address.data() + 12);
}

IPv6Address::octet_t *IPv6Address::data() { return _address.data(); }

const IPv6Address::octet_t *IPv6Address::data() const {
  return _address.data();
}

IPv6Address::octet_t const &IPv6Address::operator[](std::size_t index) const {
  return _address.at(index);
}

IPv6Address::octet_t const &IPv6Address::at(std::size_t index) const {
  return _address.at(index);
}

bool IPv6Address::isIPv4Mapped() const {
  // Check if the first 10 bytes are 0 and the next 2 bytes are 0xFF
  return std::memcmp(_address.data(),
                     "\x00\x00\x00\x00\x00\x00\x00\x00\xFF\xFF\xFF\xFF",
                     12) == 0;
}

IPv4Address IPv6Address::toIPv4() const {
  if (!isIPv4Mapped()) {
    throw std::runtime_error(
        "Cannot convert to IPv4: Not an IPv4-mapped IPv6 address");
  }
  return IPv4Address{std::array<cns::byte_t, IPv4Address::OCTET_COUNT>{
      _address.at(12), _address.at(13), _address.at(14), _address.at(15)}};
}

std::string IPv6Address::toString() const {
  std::string result;
  result.reserve(
      8 * 5); // Each group of 4 bytes can be represented as 4 hex digits + ':'

  const std::uint16_t *data =
      reinterpret_cast<const std::uint16_t *>(_address.data());
  for (std::size_t i = 0; i < OCTET_COUNT / 2; ++i) {
    HLP::Log::quickHexToString<std::uint16_t>(data[i], result.data() + i * 5);
    result[i * 5 + 4] = ':';
  }
  return result;
}

PortAddress::PortAddress(PortAddress::underlying_address_t const &port_number)
    : _port_number(port_number) {}

PortAddress::PortAddress(PortAddress::underlying_address_t &&port_number)
    : _port_number(std::move(port_number)) {}

} // namespace common_ns