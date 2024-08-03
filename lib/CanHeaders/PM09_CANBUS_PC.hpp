#pragma once
#include "can_ids.hpp"

namespace PUTM_CAN {

struct __attribute__((packed)) PcMainData {
    bool rtd : 1;
    uint32_t time;
};

const uint8_t PC_MAIN_CAN_DLC = sizeof(PcMainData);
const uint8_t PC_MAIN_FREQUENCY = 50;

const FDCAN_TxHeaderTypeDef can_tx_header_PC_MAIN_DATA {
		PC_MAIN_CAN_ID,
        FDCAN_STANDARD_ID,
        FDCAN_DATA_FRAME,
		PC_MAIN_CAN_DLC,
        FDCAN_ESI_PASSIVE,
        FDCAN_BRS_OFF,
        FDCAN_CLASSIC_CAN,
        FDCAN_NO_TX_EVENTS,
        0
};

}
