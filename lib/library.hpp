#pragma once

#include <variant>
#include <utility>

#include "hal_mocks.hpp"
#include "meta.hpp"
#include "CanHeaders/PM08-CANBUS-APPS.hpp"
#include "CanHeaders/PM08-CANBUS-AQ_CARD.hpp"


static void parse(PUTM_CAN::can_id_t received_id, std::size_t received_length, uint8_t const *data);

namespace PUTM_CAN {
    template<typename frame_t>
    frame_t get() noexcept;
}


void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    CAN_RxHeaderTypeDef rx_header{};
    uint8_t data[PUTM_CAN::MAX_CAN_MSG_SIZE];
    if (HAL_CAN_GetRxMessage(hcan, 0, &rx_header, data) not_eq HAL_OK) {
        // need error handling
        return;
    }
    parse(rx_header.IDE, rx_header.DLC, data);
}

void HAL_CAN_RxFifo0MsgPendingCallback(FDCAN_HandleTypeDef *hcan) {
    FDCAN_RxHeaderTypeDef rx_header{};
    uint8_t data[PUTM_CAN::MAX_CAN_FD_MSG_SIZE];
    if (HAL_CANFD_GetRxMessage(hcan, FDCAN_RX_FIFO0, &header, data) not_eq HAL_OK) {
        // todo: need error handling
    }
    parse(rx_header.Identifier, rx_header.DLC, data); 
}