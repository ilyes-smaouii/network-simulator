#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <initializer_list>
#include <limits>
#include <string>

#include "common-net.hpp"
#include "cpp-common/common-base.hpp"

namespace cns = common_ns;

namespace ip_stack {

// TO-DO : move everything here somewhere else; ideally, misc.hpp should be
// empty (?)

class MacAddress {
public:
  constexpr static std::size_t ADDRESS_SIZE{6};
  using underlying_address_t = std::array<cns::byte_t, ADDRESS_SIZE>;

  MacAddress() = default;
  MacAddress(const MacAddress &) = default;
  MacAddress(MacAddress &&) = default;
  MacAddress(const underlying_address_t &addr) : m_address(addr) {}
  MacAddress(std::initializer_list<cns::byte_t> init) {
    std::copy_n(init.begin(), std::min(init.size(), ADDRESS_SIZE),
                m_address.begin());
  }

  MacAddress &operator=(const MacAddress &) = default;
  MacAddress &operator=(MacAddress &&) = default;

  bool operator==(const MacAddress &other) const = default;
  // std::strong_ordering operator<=>(const MacAddress &) const = default;

protected:
  underlying_address_t m_address{};

private:
};

class IPv4SubnetMask {
public:
  constexpr static std::size_t MAX_MASK_SIZE{32};
  using mask_t = std::uint32_t;
  using prefix_length_t = std::uint8_t;
  static_assert(std::numeric_limits<prefix_length_t>::max() >= MAX_MASK_SIZE,
                "Error : prefix_length_t size too small !");

  IPv4SubnetMask() = default;
  IPv4SubnetMask(const IPv4SubnetMask &) = default;
  IPv4SubnetMask(IPv4SubnetMask &&) = default;
  IPv4SubnetMask(const prefix_length_t &prefix_length);
  IPv4SubnetMask &operator=(const IPv4SubnetMask &) = default;
  IPv4SubnetMask &operator=(IPv4SubnetMask &&) = default;

  // Returns mask with trailing 0's
  // e.g. a /24 subnet mask would yield 0xFFF0, and a /16 one 0xFF00
  mask_t toMask() const;
  std::size_t getLength() const;

  bool operator==(const IPv4SubnetMask &other) const = default;

protected:
  prefix_length_t m_prefix_length{};

private:
};

class IPv4Address {
public:
  constexpr static std::size_t OCTET_COUNT{4};
  using octet_t = cns::byte_t;
  using underlying_address_t = std::array<octet_t, OCTET_COUNT>;

  IPv4Address() = default;
  IPv4Address(const IPv4Address &) = default;
  IPv4Address(IPv4Address &&) = default;
  IPv4Address(underlying_address_t const &addr);
  // IPv4Address(std::initializer_list<octet_t> init);
  IPv4Address(octet_t const &a, octet_t const &b, octet_t const &c,
              octet_t const &d);

  IPv4Address &operator=(const IPv4Address &) = default;
  IPv4Address &operator=(IPv4Address &&) = default;

  octet_t *data();
  const octet_t *data() const;
  octet_t const &operator[](std::size_t index) const;
  octet_t const &at(std::size_t index) const;

  bool operator==(IPv4Address const &other) const = default;
  // std::strong_ordering operator<=>(const IpV4Address &) const = default;

  std::string toString() const;

protected:
  underlying_address_t m_address{};

private:
};

class IPv6Address {
public:
  constexpr static std::size_t OCTET_COUNT{16};
  using octet_t = cns::byte_t;

  using underlying_address_t = std::array<octet_t, OCTET_COUNT>;

  IPv6Address() = default;
  IPv6Address(IPv6Address const &) = default;
  IPv6Address(IPv6Address &&) = default;
  IPv6Address(underlying_address_t const &addr);
  IPv6Address(std::initializer_list<cns::byte_t> init);
  IPv6Address(IPv4Address const &ipv4_addr);
  IPv6Address(IPv4Address &&ipv4_addr);

  IPv6Address &operator=(const IPv6Address &) = default;
  IPv6Address &operator=(IPv6Address &&) = default;

  octet_t *data();
  const octet_t *data() const;
  octet_t const &operator[](std::size_t index) const;
  octet_t const &at(std::size_t index) const;

  bool isIPv4() const;
  IPv4Address toIPv4() const;

  bool operator==(IPv6Address const &other) const = default;
  // std::strong_ordering operator<=>(const IpV6Address &) const = default;

  std::string toString() const;

protected:
  underlying_address_t m_address{};

private:
};

class PortAddress {
public:
  using underlying_address_t = std::uint16_t;

  PortAddress() = default;
  PortAddress(PortAddress const &) = default;
  PortAddress(PortAddress &&) = default;
  PortAddress(underlying_address_t const &port_number);
  PortAddress(underlying_address_t &&port_number);

  bool operator==(PortAddress const &other) const = default;

protected:
  underlying_address_t m_port_number;

private:
};

static_assert(
    cns::IsAddressType<MacAddress>,
    "MacAddress does not satisfy IsAddressType concept requirements !");
static_assert(
    cns::IsAddressType<IPv4Address>,
    "IPv4Address does not satisfy IsAddressType concept requirements !");
static_assert(
    cns::IsAddressType<PortAddress>,
    "PortAddress does not satisfy IsAddressType concept requirements !");

} // namespace ip_stack

namespace std {

template <> struct hash<ip_stack::IPv4Address> {
  std::size_t operator()(ip_stack::IPv4Address const &address) const {
    return std::hash<std::uint32_t>()(
        *reinterpret_cast<const std::uint32_t *>(address.data()));
  }
};

template <> struct hash<ip_stack::IPv6Address> {
  std::size_t operator()(ip_stack::IPv6Address const &address) const {
    auto const data = reinterpret_cast<const std::uint64_t *>(address.data());
    return HLP::hashOnList<std::uint64_t>({data[0], data[1]});
    // return HLP::hashOnList<ip_stack::IPv6Address::octet_t>(
    //     {address[0], address[1], address[2], address[3], address[4],
    //     address[5],
    //      address[6], address[7], address[8], address[9], address[10],
    //      address[11], address[12], address[13], address[14], address[15]});
  }
};

} // namespace std