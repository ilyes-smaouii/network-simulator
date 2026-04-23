#pragma once

#include <cstdint>
#include <string_view>

namespace common {
namespace base {

using byte_t = std::uint8_t;
using layer_t = std::uint8_t;

enum class OsiLayer : layer_t {
  UNDEF_IDX = 0,
  PHYSICAL_IDX = 1,
  DATA_LINK_IDX = 2,
  NETWORK_IDX = 3,
  TRANSPORT_IDX = 4,
  SESSION_IDX = 5,
  PRESENTATION_IDX = 6,
  APPLICATION_IDX = 7,
};

constexpr std::string_view PHYSICAL_LAYER_STR{"PHYSICAL"};
constexpr std::string_view DATA_LINK_LAYER_STR{"DATA_LINK"};
constexpr std::string_view NETWORK_LAYER_STR{"NETWORK"};
constexpr std::string_view TRANSPORT_LAYER_STR{"TRANSPORT"};
constexpr std::string_view SESSION_LAYER_STR{"SESSION"};
constexpr std::string_view PRESENTATION_LAYER_STR{"PRESENTATION"};
constexpr std::string_view APPLICATION_LAYER_STR{"APPLICATION"};

constexpr std::string_view osi_layer_to_string(OsiLayer layer) {
  switch (static_cast<OsiLayer>(layer)) {
  case OsiLayer::PHYSICAL_IDX:
    return PHYSICAL_LAYER_STR;
  case OsiLayer::DATA_LINK_IDX:
    return DATA_LINK_LAYER_STR;
  case OsiLayer::NETWORK_IDX:
    return NETWORK_LAYER_STR;
  case OsiLayer::TRANSPORT_IDX:
    return TRANSPORT_LAYER_STR;
  case OsiLayer::SESSION_IDX:
    return SESSION_LAYER_STR;
  case OsiLayer::PRESENTATION_IDX:
    return PRESENTATION_LAYER_STR;
  case OsiLayer::APPLICATION_IDX:
    return APPLICATION_LAYER_STR;
  case OsiLayer::UNDEF_IDX:
  default:
    return "UNDEF";
  }
}

template <typename AddressType>
concept IsAddressType = true;

/*
class LayerType {
public:
  static constexpr layer_t layer_idx{OsiLayers::PHYSICAL};
}

 */

template <typename LayerType>
concept IsLayerType = true && IsAddressType<typename LayerType::address_t>;

} // namespace base
} // namespace common