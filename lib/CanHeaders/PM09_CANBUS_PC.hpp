#pragma once
#include "can_ids.hpp"

namespace PUTM_CAN {

struct __attribute__((packed)) PcMainData {
    uint8_t vehicleSpeed;
    /* Inverter temperatures */
    uint8_t frontLeftInverterTemperature : 6;
    uint8_t frontRightInverterTemperature : 6;
    uint8_t rearLeftIverterTemperature : 6;
    uint8_t rearRightIverterTemperature : 6;
    /* Motor temperatures */
    uint8_t frontLeftMotorTemperature : 6;
    uint8_t frontRightMotorTemperature : 6;
    uint8_t rearLeftMotorTemperature : 6;
    uint8_t rearRightMotorTemperature : 6;

    bool rtd : 1;
    bool inverters_ready : 1;
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
