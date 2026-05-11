#pragma once

#include "cpp-common/common-base.hpp"
#include "cpp-common/logging.hpp"
#include "cpp-common/misc.hpp"

// #include "../../common/common-net.hpp"
// #include "../../L2_datalink/mac/mac-specs.hpp"
// #include "../../common/generic-layers.hpp"
// #include "../../common/misc.hpp"
#include "../../common/ns-protocol.hpp"
#include "ip-specs.hpp"

#include <memory>
#include <unordered_map>
#include <utility>

namespace cns = common_ns;
namespace cns_p = cns::protocol;

namespace ip_stack {

struct IPv4EntityData {
public:
  using entity_id_t = cns_p::entity_id_t;

  entity_id_t m_entity_id;
  IPv4EntityBase *m_entity_ptr;

protected:
private:
};

class IPv4HandlerBase {
public:
  using entity_id_t = cns_p::entity_id_t;
  using entity_data_t = cns_p::EntityData;
  using msg_t = cns_p::Message;
  using uuid_generator_t = cns_p::uuid_generator_t;
  using entity_t = ip_stack::IPv4EntityBase;
  using ip_address_t = entity_t::address_t;

  IPv4HandlerBase();
  IPv4HandlerBase(IPv4HandlerBase const &) = default;
  IPv4HandlerBase(IPv4HandlerBase &&) = default;
  IPv4HandlerBase &operator=(IPv4HandlerBase const &) = default;
  IPv4HandlerBase &operator=(IPv4HandlerBase &&) = default;

  std::unordered_map<entity_id_t, entity_data_t> const &getEntities() const;
  std::unordered_map<entity_id_t, entity_data_t> getEntities();
  // TO-DO : decide between createEntity() (all entities entirely managed by
  // handler) and addEntities() (managed somewhere else, which means handler
  // relies on callee keeping entites alive + manual updating of internal data
  // before each method is executed)
  template <typename... Args> void createEntity(Args &&...args) {
    auto new_entity_id = m_uuid_generator->getNextUuid();
    m_entities.emplace(new_entity_id, std::forward<Args>(args)...);
  }
  void addEntities(std::initializer_list<entity_t const &> entities);
  void removeEntities(std::initializer_list<entity_t const &> entities);

  void sendMessageFromTo(ip_address_t const &from, ip_address_t const &to);

  // TO-DO : figure out how not to let call stack just grow here (call queue ?)
  void handleEncapsulatedMsg(entity_t const &entity, msg_t const &msg);
  void handleDecapsulatedMsg(entity_t const &entity, msg_t const &msg);

protected:
  // updates IPs in here
  void updateIPs();
  // TO-DO : replace with smart pointers ?
  // Requirements : each entity should have valid IP ?
  std::unordered_map<entity_id_t, entity_t const &> m_entities{};
  std::unordered_map<ip_address_t, entity_id_t> m_ip_addresses{};
  std::shared_ptr<uuid_generator_t> m_uuid_generator;

private:
};

static_assert(
    cns_p::IsHandlerType<IPv4HandlerBase>,
    "Error : IPv4HandlerBase doesn't satisfy IsHandler requirements !");

} // namespace ip_stack