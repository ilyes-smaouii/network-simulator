#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <string>


#include "common_net.hpp"

namespace cns = common_ns;

namespace common_ns {

class MacAddress {
public:
  constexpr static std::size_t ADDRESS_SIZE{6};
  using underlying_address_t = std::array<cns::byte_t, ADDRESS_SIZE>;

  MacAddress() = default;
  MacAddress(const MacAddress &) = default;
  MacAddress(MacAddress &&) = default;
  MacAddress(const underlying_address_t &addr) : _address(addr) {}
  MacAddress(std::initializer_list<cns::byte_t> init) {
    std::copy_n(init.begin(), std::min(init.size(), ADDRESS_SIZE),
                _address.begin());
  }

  MacAddress &operator=(const MacAddress &) = default;
  MacAddress &operator=(MacAddress &&) = default;

  bool operator==(const MacAddress &other) const = default;
  // std::strong_ordering operator<=>(const MacAddress &) const = default;

protected:
  underlying_address_t _address{};

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
  IPv4Address(std::initializer_list<cns::byte_t> init);

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
  underlying_address_t _address{};

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
  IPv6Address(const IPv4Address &ipv4_addr);

  IPv6Address &operator=(const IPv6Address &) = default;
  IPv6Address &operator=(IPv6Address &&) = default;

  octet_t *data();
  const octet_t *data() const;
  octet_t const &operator[](std::size_t index) const;
  octet_t const &at(std::size_t index) const;

  bool isIPv4Mapped() const;
  IPv4Address toIPv4() const;

  bool operator==(IPv6Address const &other) const = default;
  // std::strong_ordering operator<=>(const IpV6Address &) const = default;

  std::string toString() const;

protected:
  underlying_address_t _address{};

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
  underlying_address_t _port_number;

private:
};

static_assert(
    IsAddressType<MacAddress>,
    "MacAddress does not satisfy IsAddressType concept requirements !");
static_assert(
    IsAddressType<IPv4Address>,
    "MacAddress does not satisfy IsAddressType concept requirements !");
static_assert(
    IsAddressType<PortAddress>,
    "PortAddress does not satisfy IsAddressType concept requirements !");

} // namespace common_ns