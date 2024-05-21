#ifndef __DASH_H__
#define __DASH_H__

namespace PUTM_CAN {

struct __attribute__((packed)) DashMain {
	uint16_t counter;
};

const uint16_t DASH_MAIN_CAN_ID = 0x69;
const uint8_t DASH_MAIN_CAN_DLC = sizeof(DashMain);
const uint8_t DASH_MAIN_FREQUENCY = 100;

#ifndef PUTM_USE_CAN_FD

const FDCAN_TxHeaderTypeDef can_tx_header_DASH_MAIN {
	DASH_MAIN_CAN_ID,
	FDCAN_STANDARD_ID,
	FDCAN_DATA_FRAME,
	DASH_MAIN_CAN_DLC,
	FDCAN_ESI_PASSIVE,
	FDCAN_BRS_OFF,
	FDCAN_CLASSIC_CAN,
	FDCAN_NO_TX_EVENTS,
	0
};

#endif

} // PUTM_CAN
#endif // __DASH_H__
