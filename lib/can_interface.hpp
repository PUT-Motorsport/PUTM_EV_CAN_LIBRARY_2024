#ifndef CAN_INTERFACE_HPP
#define CAN_INTERFACE_HPP

#include <stdio.h>

#include <array>
#include <cstdint>
#include <variant>

#ifdef UNIT_TESTS
#include "../hal_can.hpp"
#else
#include "main.h"
#endif

#include "message_abstraction.hpp"

#include "CanHeaders/PM09-CANBUS-FRONTBOX.hpp"
#include "CanHeaders/PM09-CANBUS-REARBOX.hpp"
#include "CanHeaders/PM09-CANBUS-DASHBOARD.hpp"
#include "CanHeaders/PM09-CANBUS-AMK-FRONT-LEFT.hpp"
#include "CanHeaders/PM09_CANBUS_PC.hpp"

namespace PUTM_CAN {

class Can_interface {

    Device<DriverInput> driverInput { DRIVER_INPUT_CAN_ID };
    Device<RearboxMain> rearbox { REARBOX_MAIN_CAN_ID };
    Device<Dashboard> dashboard { DASHBOARD_MAIN_CAN_ID };
    Device<AmkFrontLeftActualValues1> amkFrontLeftActualValue1 { FRONT_LEFT_AMK_ACTUAL_VALUES_1_CAN_ID };
    Device<PcMainData> pcMainData { PC_MAIN_CAN_ID };

    std::array<Device_base*, 40> device_array = {
            &driverInput,
            &rearbox,
            &dashboard,
			&amkFrontLeftActualValue1,
			&pcMainData
    };

public:
    Can_interface() = default;

    bool parse_message(const Can_rx_message &m) {
        for(auto &device : device_array) {
            if(device->get_ID() == m.header.Identifier) {
                device->set_data(m);
                return true;
            }
        }
        return false;
    }

    DriverInput get_driver_input_main() {
        return driverInput.data;
    }

    RearboxMain get_rearbox_main() {
        return rearbox.data;
    }

    Dashboard get_dashboard() {
        return dashboard.data;
    }

    AmkFrontLeftActualValues1 get_amk_front_left_actual_values1() {
    	return amkFrontLeftActualValue1.data;
    }

    PcMainData get_pc_main_data() {
     	return pcMainData.data;
     }

    bool get_driver_input_main_new_data() {
        return driverInput.get_new_data();
    }

    bool get_dashboard_new_data() {
        return dashboard.get_new_data();
    }

    bool get_pc_new_data() {
        return pcMainData.get_new_data();
    }


};

Can_interface can;

} // namespace PUTM_CAN

void HAL_CAN_RxFifo0MsgPendingCallback(FDCAN_HandleTypeDef *hfdcan1) {
    PUTM_CAN::Can_rx_message rx { *hfdcan1, 0 };
    if(rx.status == HAL_StatusTypeDef::HAL_OK) {
        if(not PUTM_CAN::can.parse_message(rx)) {
            // Unknown message
            // Error_Handler();
        }
    }
}

#endif
