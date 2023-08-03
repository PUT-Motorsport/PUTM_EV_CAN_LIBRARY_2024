// Generated on Wed Jun 15 10:27:26 2022
#ifndef BMS_HV
#define BMS_HV

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

struct __attribute__((packed)) BMS_HV_cell_voltages {
  uint8_t cell_start;
  uint16_t v_cell_start : 12;
  uint16_t v_cell_start_plus_1 : 12;
  uint16_t v_cell_start_plus_2 : 12;
  uint16_t v_cell_start_plus_3 : 12;
  uint8_t cell_end;
};

static_assert(sizeof(BMS_HV_cell_voltages) == 8);
const uint16_t BMS_HV_VOLTAGES_CAN_ID = 0xb;
const uint8_t BMS_HV_VOLTAGES_CAN_DLC = sizeof(BMS_HV_cell_voltages);
const uint8_t BMS_HV_VOLTAGES_FREQUENCY = 100;

#ifndef PUTM_USE_CAN_FD

const CAN_TxHeaderTypeDef can_tx_header_BMS_HV_MAIN{
    BMS_HV_MAIN_CAN_ID,  0xFFF,  CAN_ID_STD, CAN_RTR_DATA,
    BMS_HV_MAIN_CAN_DLC, DISABLE};

const CAN_TxHeaderTypeDef can_tx_header_BMS_HV_VOLTAGES{
    BMS_HV_VOLTAGES_CAN_ID,  0xFFF,  CAN_ID_STD, CAN_RTR_DATA,
    BMS_HV_VOLTAGES_CAN_DLC, DISABLE};

#else

constexpr static FDCAN_TxHeaderTypeDef can_tx_header_BMS_HV_MAIN = [] {
  FDCAN_TxHeaderTypeDef temp_header{};
  temp_header.Identifier = BMS_HV_MAIN_CAN_ID;
  temp_header.IdType = FDCAN_STANDARD_ID;
  temp_header.TxFrameType = FDCAN_DATA_FRAME;
  temp_header.DataLength = FDCAN_DLC_BYTES_8;
  temp_header.ErrorStateIndicator = FDCAN_ESI_PASSIVE;
  temp_header.BitRateSwitch = FDCAN_BRS_OFF;
  temp_header.FDFormat = FDCAN_CLASSIC_CAN;
  temp_header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
  temp_header.MessageMarker = 0;
  return temp_header;
}();

constexpr static FDCAN_TxHeaderTypeDef can_tx_header_BMS_HV_cell_voltages = [] {
  FDCAN_TxHeaderTypeDef temp_header{};
  temp_header.Identifier = BMS_HV_VOLTAGES_CAN_ID;
  temp_header.IdType = FDCAN_STANDARD_ID;
  temp_header.TxFrameType = FDCAN_DATA_FRAME;
  temp_header.DataLength = FDCAN_DLC_BYTES_8;
  temp_header.ErrorStateIndicator = FDCAN_ESI_PASSIVE;
  temp_header.BitRateSwitch = FDCAN_BRS_OFF;
  temp_header.FDFormat = FDCAN_CLASSIC_CAN;
  temp_header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
  temp_header.MessageMarker = 0;
  return temp_header;
}();

#endif

}   // namespace PUTM_CAN

#endif
