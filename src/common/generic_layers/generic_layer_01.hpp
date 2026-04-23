#pragma once

#include <array>
#include <cstddef>

#include "../common_base.hpp"
#include "generic_layer.hpp"

namespace c_b = common::base;

// using mac_address_t = std::array<c_b::byte_t, ADRE>;

class MacAddress {
public:
  constexpr static std::size_t ADDRESS_SIZE{6};

  MacAddress() = default;
  MacAddress(const MacAddress &) = default;
  MacAddress(MacAddress &&) = default;
  MacAddress(const std::array<c_b::byte_t, ADDRESS_SIZE> &addr)
      : address(addr) {}
  MacAddress(std::initializer_list<c_b::byte_t> init) {
    std::copy_n(init.begin(), std::min(init.size(), ADDRESS_SIZE),
                address.begin());
  }
  MacAddress &operator=(const MacAddress &) = default;
  MacAddress &operator=(MacAddress &&) = default;
  
protected:
  std::array<c_b::byte_t, ADDRESS_SIZE> address{};

private:
};

// Physical Layer
class GenericLayer01 : public GenericLayerBase {
public:
  using address_t = MacAddress;

  static constexpr c_b::OsiLayer LAYER_IDX{c_b::OsiLayer::PHYSICAL_IDX};

protected:
private:
};

static_assert(
    c_b::IsLayerType<GenericLayer01>,
    "GenericLayer01 does not satisfy IsLayerType concept requirements !");