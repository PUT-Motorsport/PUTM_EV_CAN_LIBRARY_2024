#ifndef DV
#define DV

#include <cstdint>

namespace PUTM_CAN {

enum struct AutonomousSystemStatus : uint8_t {
	Off,
    Ready,
    Driving,
    Emergency,
    Finished,
};

struct __attribute__ ((packed)) DV_Ass{
	AutonomousSystemStatus status;
};

const uint16_t DV_ASS_CAN_ID = 0x07;
const uint8_t DV_ASS_CAN_DLC = sizeof(DV_Ass);
const uint8_t DV_ASS_FREQUENCY = 1;


enum struct DV_TC_control_status: uint8_t {
	disabled,
	current
};


struct __attribute__ ((packed)) DV_TC_control{
	uint8_t cnt;
	uint8_t crc;
	int16_t set_current;
	DV_TC_control_status device_state : 6; //
};

const uint16_t DV_TC_CAN_ID = 0x38;
const uint8_t DV_TC_CAN_DLC = sizeof(DV_TC_control);
const uint8_t DV_TC_FREQUENCY = 20;


#ifndef PUTM_USE_CAN_FD

const CAN_TxHeaderTypeDef can_tx_header_DV_ASS{
DV_ASS_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, DV_ASS_CAN_DLC, DISABLE};

#endif

} // namespace can

#endif
