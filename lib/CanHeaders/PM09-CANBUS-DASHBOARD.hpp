#ifndef __DASHBOARD_H__
#define __DASHBOARD_H__

#include "can_ids.hpp"

namespace PUTM_CAN {

struct __attribute__((packed)) DashboardMain {
    uint16_t counter;
};

const uint8_t DASHBOARD_MAIN_CAN_DLC = sizeof(DashboardMain);
const uint8_t DASHBOARD_MAIN_FREQUENCY = 100;

#ifndef PUTM_USE_CAN_FD

const FDCAN_TxHeaderTypeDef can_tx_header_DASHBOARD_MAIN {
        DASHBOARD_MAIN_CAN_ID,
        FDCAN_STANDARD_ID,
        FDCAN_DATA_FRAME,
        DASHBOARD_MAIN_CAN_DLC,
        FDCAN_ESI_PASSIVE,
        FDCAN_BRS_OFF,
        FDCAN_CLASSIC_CAN,
        FDCAN_NO_TX_EVENTS,
        0
};

#endif

} // PUTM_CAN
#endif // __DASHBOARD_H__
