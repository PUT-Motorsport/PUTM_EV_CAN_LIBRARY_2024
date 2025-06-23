#pragma once
#include "can_ids.hpp"

namespace PUTM_CAN {

struct __attribute__((packed)) DataLoggerStatus {
    uint16_t current;                  //  mA
    uint16_t voltage;                  //  mV
    bool status_triggered_current : 1; 
    bool status_triggered_voltage : 1;
    bool status_logging : 1;
    bool status_ready : 1;
    uint8_t msg_cnt;                  // Message counter
};

const uint8_t DATA_LOGGER_STATUS_CAN_DLC = sizeof(DataLoggerStatus);
const uint8_t DATA_LOGGER_STATUS_FREQUENCY = 50; // Hz

const FDCAN_TxHeaderTypeDef can_tx_header_DATA_LOGGER_STATUS{
    DATA_LOGGER_STATUS_CAN_ID, FDCAN_STANDARD_ID, FDCAN_DATA_FRAME, 
    DATA_LOGGER_STATUS_CAN_DLC, FDCAN_ESI_PASSIVE, FDCAN_BRS_OFF, 
    FDCAN_CLASSIC_CAN, FDCAN_NO_TX_EVENTS, 0};

} // namespace PUTM_CAN