#include <cassert>
#include <iostream>
// #include <locale>

#include "common/common-net.hpp"
#include "common/ns-protocol.hpp"
#include "cpp-common/common-base.hpp"

// #include "../common/common-net.hpp"
// #include "../common/generic-layers.hpp"
#include "L2_datalink\MAC\mac-specs.hpp"
#include "L3_network/IP/ip-handler.hpp"
#include "L3_network/IP/ip-specs.hpp"
#include "common/misc.hpp"

// #include "../L4_transport/TCP/tcp-specs.hpp"

namespace cns = common_ns;

int main(int argc, char *argv[]) {
  std::cout << "Entering test.." << std::endl;

  ip_stack::IPv4SubnetMask le_subnet_mask{24}; // IP/24 addresses
  ip_stack::IPv4HandlerBase le_handler{};

  auto alice_mac = ip_stack::MacEntity();
  ip_stack::IPv4EntityBase alice_ip({192, 0, 0, 1});
  alice_ip.setSubnetMask(le_subnet_mask);

  auto bob_mac = ip_stack::MacEntity();
  ip_stack::IPv4EntityBase bob_ip;
  bob_ip.setAddress({192, 0, 0, 2});
  bob_ip.setSubnetMask(le_subnet_mask);

  ip_stack::IPv4EntityBase morgan_ip(
      {192, 0, 1, 0}); // Morgan on a different network from Alice and Bob
  morgan_ip.setSubnetMask(le_subnet_mask);

  // le_handler.addEntities({alice_ip, bob_ip, morgan_ip});

  std::string bob_msg_str{"Hello, Bob !"}, morgan_msg_str{"Hello, Morgan !"};
  cns::protocol::Message le_msg_bob{ip_stack::IpMsgFromString(bob_msg_str)};
  cns::protocol::Message le_msg_morgan{
      ip_stack::IpMsgFromString(morgan_msg_str)};

  //   alice_ip.encapsulateMsg(le_msg_bob, bob_ip.getAddress());
  //   alice_ip.encapsulateMsg(le_msg_morgan, morgan_ip.getAddress());

  // auto bob_msgs = le_handler.getReceivedMessages(bob_ip);
  // auto morgan_msgs = le_handler.getReceivedMessages(morgan_ip);

  // assert(bob_msgs.empty())
  // assert(morgan_msgs.empty())

  // le_handler.sendMessageFromTo(alice_ip.getAddress(), bob_ip.getAddress(),
  // le_msg_bob)
  //
  // le_handler.sendMessageFromTo(alice_ip.getAddress(), morgan_ip.getAddress(),
  // le_msg_morgan)

  // bob_msgs = le_handler.getReceivedMessages(bob_ip);
  // morgan_msgs = le_handler.getReceivedMessages(morgan_ip);
  // assert(!bob_msgs.empty())
  // assert(!morgan_msgs.empty())

  // auto bob_last_msg_str = ip_stack::StringFromMsg(bob_msgs.back());
  // auto morgan_last_msg_str = ip_stack::StringFromMsg(morgan_msgs.back());

  // assert(bob_last_msg_str.equals("bob_msg_str"))
  // assert(bob_last_msg_str.equals("morgan_msg_str"))

  std::cout << "Exiting test.." << std::endl;
  return 0;
}