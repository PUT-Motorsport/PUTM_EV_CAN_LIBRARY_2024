/*
 * PM09-CANBUS-BMS-HV.hpp
 *
 *  Created on: Jun 28, 2024
 *      Author: ketirange
 */

#ifndef INC_PUTM_EV_CAN_LIBRARY_2024_LIB_CANHEADERS_PM09_CANBUS_BMS_HV_HPP_
#define INC_PUTM_EV_CAN_LIBRARY_2024_LIB_CANHEADERS_PM09_CANBUS_BMS_HV_HPP_

#include <cstdint>

namespace PUTM_CAN {

enum struct BMS_HV_states : uint8_t {
  AIR_opened,            // normal
  AIR_closed,            // normal
  Precharge,             // normal
  Charger_connected,     // normal
  Unbalanced,            // warning
  Unbalanced_critical,   // shut down
  Voltage_low,           // shut down
  Voltage_high,          // shut down
  Temp_high,             // shut down
  Current_high,          // shut down
};

struct __attribute__((packed)) BMS_HV_main {
  uint16_t voltage_sum;
  int16_t current;
  uint8_t temp_max;
  uint8_t temp_avg;                 // in Celsius
  uint16_t soc : 10;                // state of charge
  BMS_HV_states device_state : 6;   //
};

const uint16_t BMS_HV_MAIN_CAN_ID = 0xa;
const uint8_t BMS_HV_MAIN_CAN_DLC = sizeof(BMS_HV_main);
const uint8_t BMS_HV_MAIN_FREQUENCY = 100;

//struct __attribute__((packed)) BMS_HV_cell_voltages {
//  uint8_t cell_start;
//  uint16_t v_cell_start : 12;
//  uint16_t v_cell_start_plus_1 : 12;
//  uint16_t v_cell_start_plus_2 : 12;
//  uint16_t v_cell_start_plus_3 : 12;
//  uint8_t cell_end;
//};
//
//static_assert(sizeof(BMS_HV_cell_voltages) == 8);
//const uint16_t BMS_HV_VOLTAGES_CAN_ID = 0xb;
//const uint8_t BMS_HV_VOLTAGES_CAN_DLC = sizeof(BMS_HV_cell_voltages);
//const uint8_t BMS_HV_VOLTAGES_FREQUENCY = 100;


const FDCAN_TxHeaderTypeDef can_tx_header_BMS_HV_MAIN {
		BMS_HV_MAIN_CAN_ID,
        FDCAN_STANDARD_ID,
        FDCAN_DATA_FRAME,
		BMS_HV_MAIN_CAN_DLC,
        FDCAN_ESI_PASSIVE,
        FDCAN_BRS_OFF,
        FDCAN_CLASSIC_CAN,
        FDCAN_NO_TX_EVENTS,
        0
};

}   // namespace PUTM_CAN



#endif /* INC_PUTM_EV_CAN_LIBRARY_2024_LIB_CANHEADERS_PM09_CANBUS_BMS_HV_HPP_ */
