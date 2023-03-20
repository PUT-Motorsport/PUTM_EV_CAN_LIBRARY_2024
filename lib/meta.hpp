#pragma once

#include <cstdint>

namespace PUTM_CAN {
constexpr std::size_t MAX_CAN_MSG_SIZE{8};
constexpr std::size_t MAX_CAN_FD_MSG_SIZE{64};
constexpr std::size_t MAX_MESSAGE_SIZE{MAX_CAN_FD_MSG_SIZE}; // todo: easy space optimization
constexpr std::size_t NUM_PARSED_MSG{32};
using can_id_t = uint32_t;
}  // namespace PUTM_CAN

