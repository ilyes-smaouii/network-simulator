#include <iostream>
// #include <locale>

#include "cpp-common/common-base.hpp"

// #include "../common/common-net.hpp"
// #include "../common/generic-layers.hpp"
// #include "../common/misc.hpp"
#include "L2_datalink\MAC\mac-specs.hpp"
#include "L3_network/IP/ip-specs.hpp"
// #include "../L4_transport/TCP/tcp-specs.hpp"

int main(int argc, char *argv[]) {
  std::cout << "Entering test.." << std::endl;
  auto alice_mac = ip_stack::MacEntity();
  ip_stack::IpEntityBase alice_ip;
  // alice_ip.setL2Output(alice_mac);

  auto bob_mac = ip_stack::MacEntity();
  ip_stack::IpEntityBase bob_ip;
  // bob_ip.setL2Output(bob_mac);

  // alice_ip.getL2Output();
  // bob_ip.getL2Output();

  std::cout << "Exiting test.." << std::endl;
  return 0;
}