#pragma once

#include <cstdint>
#include <unordered_map>

#include "cpp-common/containers.hpp"
#include "cpp-common/misc.hpp"

// #include "L3_network/IP/ip-specs.hpp"
#include "common-net.hpp"
#include "misc.hpp"

namespace hlp_cont = HLP::Containers;

namespace common_ns {
namespace protocol {
using protocol_version_t = std::uint64_t;
using entity_id_t = std::uint64_t;
using uuid_t = std::uint64_t;
using uuid_generator_t = HLP::SingletonUuidGenerator<uuid_t>;

constexpr protocol_version_t DEFAULT_PROTOCOL_VERSION{1};

// TO-DO : figure out how different classes/entities are gonna interact with
// each other

// - Going down/up vs horizontal - encapsulate/decapsulate enough ?
// - Simple buffers vs. stream of bits (e.g. for Physical layer) --> flexible
// idea for a Message ?
// - Different data in addition to header + payload depending on layers and
// protocols --> how do I make it generic ?

class Message {
public:
  Message() = default;
  Message(const Message &) = default;
  Message(Message &&) = default;
  Message &operator=(const Message &) = default;
  Message &operator=(Message &&) = default;

protected:
private:
};

class MessageMetaData {
public:
  MessageMetaData() = default;
  MessageMetaData(const MessageMetaData &) = default;
  MessageMetaData(MessageMetaData &&) = default;
  MessageMetaData &operator=(const MessageMetaData &) = default;
  MessageMetaData &operator=(MessageMetaData &&) = default;

protected:
  protocol_version_t m_protocol_version{};
  entity_id_t src_id{};
  entity_id_t dst_id{};
  OsiLayer src_layer{};

private:
};

class EntityData {
public:
  EntityData() = default;
  EntityData(const EntityData &) = default;
  EntityData(EntityData &&) = default;
  EntityData &operator=(const EntityData &) = default;
  EntityData &operator=(EntityData &&) = default;

protected:
  OsiLayer m_layer{};

private:
};

// TO-DO : decide whether or not I keep this
class NsHandlerBase {
public:
  NsHandlerBase() = default;
  NsHandlerBase(const NsHandlerBase &) = default;
  NsHandlerBase(NsHandlerBase &&) = default;
  NsHandlerBase &operator=(const NsHandlerBase &) = default;
  NsHandlerBase &operator=(NsHandlerBase &&) = default;

protected:
  std::unordered_map<entity_id_t, EntityData> m_entities{};

private:
};

template <typename T>
// TO-DO : specify requirements
concept IsMsgType = hlp_cont::IsUsableAsBuffer<T>;

template <typename T>
// TO-DO : specify requirements
concept IsDynamicSizeMsgType = hlp_cont::IsUsableAsDynamicSizeBuffer<T>;

template <typename T>
concept IsHandlerType =
    false || requires(T handler, typename T::entity_t const &entity,
                      typename T::msg_t const &msg) {
      handler.handleEncapsulatedMsg(entity, msg);
      handler.handleDecapsulatedMsg(entity, msg);
    };

// TO-DO : fix this
static_assert(true || IsHandlerType<NsHandlerBase>,
              "Error : NsHandlerBase doesn't satisfy IsHandlerType concept !");

} // namespace protocol
} // namespace common_ns