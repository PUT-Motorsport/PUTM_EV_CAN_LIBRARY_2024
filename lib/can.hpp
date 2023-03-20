#pragma once

#include "hal_mocks.hpp"
#include <cstdint>

#include "CanHeaders/can_headers.hpp"
#include "meta.hpp"

namespace PUTM_CAN {

namespace filter {
constexpr CAN_FilterTypeDef id(can_id_t id1, can_id_t id2) noexcept {

  // always uses the FIFO0
  return CAN_FilterTypeDef{
      .FilterIdHigh = 0,
      .FilterIdLow = 0,
      .FilterMaskIdHigh = 0,
      .FilterMaskIdLow = 0,
      .FilterFIFOAssignment = 0, // FIFO0
      .FilterBank = 0,
      .FilterMode = 0,
      .FilterScale = 0,
      .SlaveStartFilterBank = 0,
  };
}

constexpr CAN_FilterTypeDef mask(uint32_t mask, can_id_t filter) noexcept {
  // always uses the FIFO0
  return CAN_FilterTypeDef{
      .FilterIdHigh = 0,
      .FilterIdLow = 0,
      .FilterMaskIdHigh = 0,
      .FilterMaskIdLow = 0,
      .FilterFIFOAssignment = 0,
      .FilterBank = 0,
      .FilterMode = 0,
      .FilterScale = 0,
      .SlaveStartFilterBank = 0,
  };
}

constexpr CAN_FilterTypeDef null_filter{
    .FilterIdHigh = 0,
    .FilterIdLow = 0,
    .FilterMaskIdHigh = 0,
    .FilterMaskIdLow = 0,
    .FilterFIFOAssignment = 0,
    .FilterBank = 0,
    .FilterMode = 0,
    .FilterScale = 0,
    .SlaveStartFilterBank = 0,
};

} // namespace filter

class CAN {
public:
  constexpr CAN(CAN_HandleTypeDef *handle,
                CAN_FilterTypeDef const *filter) noexcept
      : handle(handle), mailbox(0) {
    if (HAL_CAN_ConfigFilter(handle, filter) not_eq HAL_OK) {
      Error_Handler();
    }
    if (HAL_CAN_Start(handle) not_eq HAL_OK) {
      Error_Handler();
    }
    if (HAL_CAN_ActivateNotification(handle, CAN_IT_RX_FIFO0_MSG_PENDING) not_eq
        HAL_OK) {
      Error_Handler();
    }
  }

  template <typename frame_t> bool send(frame_t const &frame) noexcept {
    static_assert(frame_id<frame_t> not_eq invalid_can_id, "Wrong type passed");
    CAN_TxHeaderTypeDef tx_header{
        .IDE = frame_id<frame_t>,
        .DLC = sizeof(frame_t),
        .ExtId = 0,
        .RTR = 0,
    };

    return HAL_OK == HAL_CAN_AddTxMessage(handle, &tx_header, &frame, &mailbox);
  }

  bool send_raw(can_id_t id, uint8_t const *data, std::size_t size) noexcept {
    CAN_TxHeaderTypeDef tx_header{
        .IDE = id,
        .ExtId = 0,
        .RTR = 0,
        .DLC = 0,
    };
    return HAL_OK == HAL_CAN_AddTxMessage(handle, &tx_header, data, &mailbox);
  }

private:
  CAN_HandleTypeDef *handle;
  uint32_t mailbox;
};

class FDCAN {
  constexpr FDCAN(FDCAN_HandleTypeDef *handle,
                  FDCAN_FilterTypeDef const *filter);
};

} // namespace PUTM_CAN