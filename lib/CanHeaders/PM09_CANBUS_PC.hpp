#pragma once
#include "can_ids.hpp"

namespace PUTM_CAN {

struct __attribute__((packed)) PcTemperatureData {
    uint8_t rearRightInverterTemperature;  // Range 20-100
    uint8_t rearLeftInverterTemperature;   // Range 20-100
    uint8_t rearRightMotorTemperature;     // Range 20-130
    uint8_t rearLeftMotorTemperature;      // Range 20-130
    uint8_t frontRightInverterTemperature; // Range 20-100
    uint8_t frontLeftInverterTemperature;  // Range 20-100
    uint8_t frontRightMotorTemperature;    // Range 20-130
    uint8_t frontLeftMotorTemperature;     // Range 20-130
};

const uint8_t PC_TEMPERATURE_CAN_DLC = sizeof(PcTemperatureData);
const uint8_t PC_TEMPERATURE_FREQUENCY = 50;

const FDCAN_TxHeaderTypeDef can_tx_header_PC_TEMPERATURE_DATA{
    PC_TEMPERATURE_CAN_ID, FDCAN_STANDARD_ID, FDCAN_DATA_FRAME, PC_TEMPERATURE_CAN_DLC, FDCAN_ESI_PASSIVE, FDCAN_BRS_OFF, FDCAN_CLASSIC_CAN, FDCAN_NO_TX_EVENTS, 0};

struct __attribute__((packed)) PcMainData {
    uint8_t vehicleSpeed : 16;                  
    uint8_t torqueCurrent : 16;                                               
    bool invertersReady : 1;                   // 1 bit
    bool rtd : 1;                              // 1 bit
    //Instead of sending information about each inverter individually, we send the inverter index and its status
    uint16_t inverterErrorIdx;
    uint8_t  inverterIdx : 4;                // 4 bits
    bool inverterStatus : 1;         // 1 bit
};

const uint8_t PC_MAIN_CAN_DLC = sizeof(PcMainData);
const uint8_t PC_MAIN_FREQUENCY = 50;

const FDCAN_TxHeaderTypeDef can_tx_header_PC_MAIN_DATA{
    PC_MAIN_CAN_ID, FDCAN_STANDARD_ID, FDCAN_DATA_FRAME, PC_MAIN_CAN_DLC, FDCAN_ESI_PASSIVE, FDCAN_BRS_OFF, FDCAN_CLASSIC_CAN, FDCAN_NO_TX_EVENTS, 0};


struct __attribute__((packed)) PcLapTimerData {
    uint16_t currentLapTime;  
    uint16_t bestLapTime;  
    int16_t delta_time;   
    uint8_t lap_counter;        
};

const uint8_t PC_LAP_TIMER_CAN_DLC = sizeof(PcLapTimerData);
const uint8_t PC_LAP_TIMER_FREQUENCY = 50; 

const FDCAN_TxHeaderTypeDef can_tx_header_PC_LAP_TIMER_DATA{
    PC_LAP_TIMER_CAN_ID, FDCAN_STANDARD_ID, FDCAN_DATA_FRAME, PC_LAP_TIMER_CAN_DLC, FDCAN_ESI_PASSIVE, FDCAN_BRS_OFF, FDCAN_CLASSIC_CAN, FDCAN_NO_TX_EVENTS, 0};

} // namespace PUTM_CAN
