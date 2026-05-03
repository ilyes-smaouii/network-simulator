#pragma once

#include <cstdint>
#include <string_view>

namespace common_ns {

using byte_t = std::uint8_t;
using layer_t = std::uint8_t;

enum class OsiLayer : layer_t {
  UNDEF_IDX = 0,
  PHYSICAL_IDX = 1,
  DATALINK_IDX = 2,
  NETWORK_IDX = 3,
  TRANSPORT_IDX = 4,
  SESSION_IDX = 5,
  PRESENTATION_IDX = 6,
  APPLICATION_IDX = 7,
};

constexpr std::string_view PHYSICAL_LAYER_SV{"PHYSICAL"};
constexpr std::string_view DATA_LINK_LAYER_SV{"DATA_LINK"};
constexpr std::string_view NETWORK_LAYER_SV{"NETWORK"};
constexpr std::string_view TRANSPORT_LAYER_SV{"TRANSPORT"};
constexpr std::string_view SESSION_LAYER_SV{"SESSION"};
constexpr std::string_view PRESENTATION_LAYER_SV{"PRESENTATION"};
constexpr std::string_view APPLICATION_LAYER_SV{"APPLICATION"};

constexpr std::string_view osi_layer_to_sv(OsiLayer layer) {
  switch (static_cast<OsiLayer>(layer)) {
  case OsiLayer::PHYSICAL_IDX:
    return PHYSICAL_LAYER_SV;
  case OsiLayer::DATALINK_IDX:
    return DATA_LINK_LAYER_SV;
  case OsiLayer::NETWORK_IDX:
    return NETWORK_LAYER_SV;
  case OsiLayer::TRANSPORT_IDX:
    return TRANSPORT_LAYER_SV;
  case OsiLayer::SESSION_IDX:
    return SESSION_LAYER_SV;
  case OsiLayer::PRESENTATION_IDX:
    return PRESENTATION_LAYER_SV;
  case OsiLayer::APPLICATION_IDX:
    return APPLICATION_LAYER_SV;
  case OsiLayer::UNDEF_IDX:
  default:
    return "UNDEF";
  }
}

template <typename AddressType>
concept IsAddressType =
    true && requires(AddressType const &a, AddressType const &b) {
      { a == b } -> std::convertible_to<const bool>;
      { a != b } -> std::convertible_to<const bool>;
    };

template <typename T>
concept IsAddressableEntity =
    IsAddressType<typename T::address_t> && requires(T const layer_protocol) {
      typename T::address_t;
      {
        layer_protocol.getAddress()
      } -> std::convertible_to<const typename T::address_t>;
    };

// template <typename LayerType>
// concept IsLayerType = requires(LayerType const &layer) {
//   { LayerType::LAYER_IDX } -> std::convertible_to<OsiLayer const &>;
// };

} // namespace common_ns