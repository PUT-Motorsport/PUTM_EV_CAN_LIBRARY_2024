#pragma once

#include "can_ids.hpp"

namespace PUTM_CAN {

struct __attribute__((packed)) PduData {
 //do zupełnienia
 };

const uint8_t PDU_DATA_CAN_DLC = sizeof(PduData);
const uint8_t PDU_DATA_FREQUENCY = 50;

const FDCAN_TxHeaderTypeDef can_tx_header_PDU_DATA{
    PDU_DATA_CAN_ID, FDCAN_STANDARD_ID, FDCAN_DATA_FRAME, PDU_DATA_CAN_DLC, FDCAN_ESI_PASSIVE, FDCAN_BRS_OFF, FDCAN_CLASSIC_CAN, FDCAN_NO_TX_EVENTS, 0};
}