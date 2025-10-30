#include "../common/common_base.hpp"

namespace c_b = common::base;

class TCPEntity {
public:
  using layer_t = c_b::layer_t;

  TCPEntity();

  static constexpr layer_t LAYER{c_b::OsiLayers::TRANSPORT};

protected:
private:
};