#pragma once
#include <cstdint>

/* Primary Can Bus */
const uint16_t DRIVER_INPUT_CAN_ID = 0x05;
const uint16_t PC_MAIN_CAN_ID = 0x10;
const uint16_t PC_LAP_TIMER_CAN_ID = 0x11;
const uint16_t PC_TEMPERATURE_CAN_ID = 0x60;
const uint16_t DASHBOARD_CAN_ID = 0x15;
const uint16_t REARBOX_SAFETY_CAN_ID = 0x25;
const uint16_t REARBOX_TEMPERATURE_CAN_ID = 0x26;
const uint16_t REARBOX_MISCELLANEOUS_CAN_ID = 0x27;
const uint16_t PDU_CHANNEL_CAN_ID = 0x30;
const uint16_t PDU_DATA_CAN_ID = 0x31;
const uint16_t FRONT_DATA_CAN_ID = 0x35;
const uint16_t BMS_HV_MAIN_CAN_ID = 0x45;
const uint16_t BMS_LV_MAIN_CAN_ID = 0x55;
const uint16_t BMS_LV_TEMPERATURE_CAN_ID = 0x56;
const uint16_t DATA_LOGGER_CAN_ID = 0x57;

/* Secondary Can Bus */
constexpr uint16_t FRONT_RIGHT_AMK_ACTUAL_VALUES_1_CAN_ID = 0x286; // + n
constexpr uint16_t FRONT_RIGHT_AMK_ACTUAL_VALUES_2_CAN_ID = 0x287; // + n
constexpr uint16_t FRONT_RIGHT_AMK_SETPOINTS_1_CAN_ID = 0x185;     // + n

constexpr uint16_t REAR_RIGHT_AMK_ACTUAL_VALUES_1_CAN_ID = 0x284; // + n
constexpr uint16_t REAR_RIGHT_AMK_ACTUAL_VALUES_2_CAN_ID = 0x285; // + n
constexpr uint16_t REAR_RIGHT_AMK_SETPOINTS_1_CAN_ID = 0x184; // + n

constexpr uint16_t REAR_LEFT_AMK_ACTUAL_VALUES_1_CAN_ID = 0x282; // + n
constexpr uint16_t REAR_LEFT_AMK_ACTUAL_VALUES_2_CAN_ID = 0x283; // + n
constexpr uint16_t REAR_LEFT_AMK_SETPOINTS_1_CAN_ID = 0x183; // + n

constexpr uint16_t FRONT_LEFT_AMK_ACTUAL_VALUES_1_CAN_ID = 0x288; // + n
constexpr uint16_t FRONT_LEFT_AMK_ACTUAL_VALUES_2_CAN_ID = 0x289; // + n
constexpr uint16_t FRONT_LEFT_AMK_SETPOINTS_1_CAN_ID = 0x186; // + n




