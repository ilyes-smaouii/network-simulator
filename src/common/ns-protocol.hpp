#pragma once

#include <cstdint>
#include <unordered_map>

#include "common-net.hpp"

namespace common_ns {
namespace protocol {
using protocol_version_t = std::uint64_t;
using entity_id_t = std::uint64_t;

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
concept IsHandlerType = requires(T handler, entity_id_t const &entity) {
  handler.handleEncapsulatedMsg(entity);
  handler.handleDecapsulatedMsg(entity);
};

} // namespace protocol
} // namespace common_ns