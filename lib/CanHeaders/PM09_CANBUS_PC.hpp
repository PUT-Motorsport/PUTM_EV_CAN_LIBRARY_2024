#pragma once
#include "can_ids.hpp"

namespace PUTM_CAN {

struct __attribute__((packed)) PcTemperatureData {
    uint8_t rearRightInverterTemperature : 7;  // Range 20-100
    uint8_t rearLeftInverterTemperature : 7;   // Range 20-100
    uint8_t rearRightMotorTemperature : 7;     // Range 20-130
    uint8_t rearLeftMotorTemperature : 7;      // Range 20-130
    uint8_t frontRightInverterTemperature : 7; // Range 20-100
    uint8_t frontLeftInverterTemperature : 7;  // Range 20-100
    uint8_t frontRightMotorTemperature : 7;    // Range 20-130
    uint8_t frontLeftMotorTemperature : 7;     // Range 20-130
};

const uint8_t PC_TEMPERATURE_CAN_DLC = sizeof(PcTemperatureData);
const uint8_t PC_TEMPERATURE_FREQUENCY = 50;

const FDCAN_TxHeaderTypeDef can_tx_header_PC_TEMPERATURE_DATA{
    PC_TEMPERATURE_CAN_ID, FDCAN_STANDARD_ID, FDCAN_DATA_FRAME, PC_TEMPERATURE_CAN_DLC, FDCAN_ESI_PASSIVE, FDCAN_BRS_OFF, FDCAN_CLASSIC_CAN, FDCAN_NO_TX_EVENTS, 0};

struct __attribute__((packed)) PcMainData {
    uint8_t vehicleSpeed : 6;                  
    uint8_t power : 6;                         
    uint16_t rpm : 15;                         
    bool invertersReady : 1;                   // 1 bit
    bool rtd : 1;                              // 1 bit
    bool inv_FL_status : 1;                    // Status, 1 bit
    bool inv_FR_status : 1;                    // Status, 1 bit
    bool inv_RL_status : 1;                    // Status, 1 bit
    bool inv_RR_status : 1;                    // Status, 1 bit
    bool inv_FL_error : 1;                     // Error, 1 bit
    bool inv_FR_error : 1;                     // Error, 1 bit
    bool inv_RL_error : 1;                     // Error, 1 bit
    bool inv_RR_error : 1;                     // Error, 1 bit
};

const uint8_t PC_MAIN_CAN_DLC = sizeof(PcMainData);
const uint8_t PC_MAIN_FREQUENCY = 50;

const FDCAN_TxHeaderTypeDef can_tx_header_PC_MAIN_DATA{
    PC_MAIN_CAN_ID, FDCAN_STANDARD_ID, FDCAN_DATA_FRAME, PC_MAIN_CAN_DLC, FDCAN_ESI_PASSIVE, FDCAN_BRS_OFF, FDCAN_CLASSIC_CAN, FDCAN_NO_TX_EVENTS, 0};

} // namespace PUTM_CAN
