#include <cstdint>

namespace common {
namespace base {

using layer_t = std::uint8_t;

enum OsiLayers : layer_t {
  PHYSICAL = 1,
  DATA_LINK = 2,
  NETWORK = 3,
  TRANSPORT = 4,
  SESSION = 5,
  PRESENTATION = 6,
  APPLICATION = 7,
};

} // namespace base
} // namespace common