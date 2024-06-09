#pragma once
#include <cstdint>

/* Primary Can Bus */
const uint16_t DRIVER_INPUT_CAN_ID   = 0x05;
const uint16_t PC_MAIN_CAN_ID 		 = 0x10;
const uint16_t DASHBOARD_MAIN_CAN_ID = 0x15;
const uint16_t REARBOX_MAIN_CAN_ID   = 0x25;
const uint16_t FRONT_DATA_CAN_ID     = 0x35;
/* Secondary Can Bus */
constexpr uint16_t FRONT_LEFT_AMK_ACTUAL_VALUES_1_CAN_ID = 0x282 + 1;  // + n
constexpr uint16_t FRONT_LEFT_AMK_ACTUAL_VALUES_2_CAN_ID = 0x284 + 1;  // + n
constexpr uint16_t FRONT_LEFT_AMK_SETPOINTS_1_CAN_ID = 0x183 + 1;  // + n
