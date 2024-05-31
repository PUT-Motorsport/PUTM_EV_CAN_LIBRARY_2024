#ifndef __REARBOX_H__
#define __REARBOX_H__

#include "can_ids.hpp"

namespace PUTM_CAN {

struct __attribute__((packed)) RearboxMain {
    bool safety_rfu1 :1;
    bool safety_rfu2 :1;
    bool safety_asms :1;
    bool safety_fw :1;
    bool safety_hv :1;
    bool safety_res :1;
    bool safety_hvd :1;
    bool safety_inv :1;
    bool safety_wheel_fl :1;
    bool safety_wheel_fr :1;
    bool safety_wheel_rl :1;
    bool safety_wheel_rr :1;
//    uint8_t mono_temperature;
//    uint8_t water_temperature1;
//    uint8_t water_temperature2;
//    uint8_t analog_input1;
//    uint8_t analog_input2;
//    uint8_t water_pressure1;
//    uint8_t water_pressure2;
//    uint16_t hain_analog_potentiometer_r;
//    uint16_t hain_analog_potentiometer_l;
};

const uint8_t REARBOX_MAIN_CAN_DLC = sizeof(RearboxMain);
const uint8_t REARBOX = 100;

#ifndef PUTM_USE_CAN_FD

const FDCAN_TxHeaderTypeDef can_tx_header_REARBOX_MAIN {
        REARBOX_MAIN_CAN_ID,
        FDCAN_STANDARD_ID,
        FDCAN_DATA_FRAME,
        REARBOX_MAIN_CAN_DLC,
        FDCAN_ESI_PASSIVE,
        FDCAN_BRS_OFF,
        FDCAN_CLASSIC_CAN,
        FDCAN_NO_TX_EVENTS,
        0
};

#endif

} // PUTM_CAN
#endif // __REARBOX_H__
