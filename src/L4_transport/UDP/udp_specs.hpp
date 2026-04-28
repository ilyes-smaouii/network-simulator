#pragma once

#include "../../common/common_net.hpp"

namespace cns = common_ns;

class UDPEntity {
public:
  using layer_t = cns::layer_t;

  UDPEntity();

  static constexpr cns::OsiLayer LAYER{cns::OsiLayer::TRANSPORT_IDX};

protected:
private:
};