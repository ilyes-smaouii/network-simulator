// #include "../../common/common_net.hpp"
// #include "../../common/generic_layers.hpp"
// #include "../../common/misc.hpp"

#include "ip_specs.hpp"
#include "../../L2_datalink/mac/mac_specs.hpp"

namespace cns = common_ns;

namespace ip_stack {

// IpEntity le_entity;

void testFun() {
  IpEntity<MacEntity> ip_entity;

  auto mac_entity = MacEntity();
  ip_entity.setL2Output(mac_entity);
  // ip_entity.setL2Output(IpEntity{});
}

} // namespace ip_stack