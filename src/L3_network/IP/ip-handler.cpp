#include <cstdint>

#include "cpp-common/misc.hpp"

#include "ip-handler.hpp"

namespace ip_stack {
IPv4HandlerBase::IPv4HandlerBase()
    : m_uuid_generator(uuid_generator_t::getInstancePtr()) {}
} // namespace ip_stack