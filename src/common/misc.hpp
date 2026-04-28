#pragma once

#include <array>
#include <cstddef>
#include <string>

#include "common_net.hpp"

namespace cns = common_ns;

namespace common_ns {

class MacAddress {
public:
  constexpr static std::size_t ADDRESS_SIZE{6};

  MacAddress() = default;
  MacAddress(const MacAddress &) = default;
  MacAddress(MacAddress &&) = default;
  MacAddress(const std::array<cns::byte_t, ADDRESS_SIZE> &addr)
      : address(addr) {}
  MacAddress(std::initializer_list<cns::byte_t> init) {
    std::copy_n(init.begin(), std::min(init.size(), ADDRESS_SIZE),
                address.begin());
  }

  MacAddress &operator=(const MacAddress &) = default;
  MacAddress &operator=(MacAddress &&) = default;

  bool operator==(const MacAddress &other) const = default;
  // std::strong_ordering operator<=>(const MacAddress &) const = default;

protected:
  std::array<cns::byte_t, ADDRESS_SIZE> address{};

private:
};

class IPv4Address {
public:
  constexpr static std::size_t OCTET_COUNT{4};
  using octet_t = cns::byte_t;

  using address_t = std::array<octet_t, OCTET_COUNT>;

  IPv4Address() = default;
  IPv4Address(const IPv4Address &) = default;
  IPv4Address(IPv4Address &&) = default;
  IPv4Address(const std::array<cns::byte_t, OCTET_COUNT> &addr);
  IPv4Address(std::initializer_list<cns::byte_t> init);

  IPv4Address &operator=(const IPv4Address &) = default;
  IPv4Address &operator=(IPv4Address &&) = default;

  octet_t *data();
  const octet_t *data() const;
  octet_t const &operator[](std::size_t index) const;
  octet_t const &at(std::size_t index) const;

  bool operator==(const IPv4Address &other) const = default;
  // std::strong_ordering operator<=>(const IpV4Address &) const = default;

  std::string toString() const;

protected:
  address_t _address{};

private:
};

class IPv6Address {
public:
  constexpr static std::size_t OCTET_COUNT{16};
  using octet_t = cns::byte_t;

  using address_t = std::array<octet_t, OCTET_COUNT>;

  IPv6Address() = default;
  IPv6Address(const IPv6Address &) = default;
  IPv6Address(IPv6Address &&) = default;
  IPv6Address(const std::array<cns::byte_t, OCTET_COUNT> &addr);
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

  bool operator==(const IPv6Address &other) const = default;
  // std::strong_ordering operator<=>(const IpV6Address &) const = default;

  std::string toString() const;
  
protected:
  address_t _address{};

private:
};

static_assert(
    IsAddressType<MacAddress>,
    "MacAddress does not satisfy IsAddressType concept requirements !");
static_assert(
    IsAddressType<IPv4Address>,
    "MacAddress does not satisfy IsAddressType concept requirements !");

} // namespace common_ns