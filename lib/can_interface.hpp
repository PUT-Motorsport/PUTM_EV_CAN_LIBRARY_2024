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

namespace PUTM_CAN {

class Can_interface {
    Device<DriverInput> driverInput { DRIVER_INPUT_CAN_ID };
    Device<RearboxMain> rearbox { DRIVER_INPUT_CAN_ID };
    Device<DashboardMain> dashboard { DRIVER_INPUT_CAN_ID };

    std::array<Device_base*, 40> device_array = {
            &driverInput,
            &rearbox,
            &dashboard,
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

    DashboardMain get_dashboard_main() {
        return dashboard.data;
    }

    bool get_driver_input_main_new_data() {
        return driverInput.get_new_data();
    }

    bool get_dashboard_main_new_data() {
        return dashboard.get_new_data();
    }

};

Can_interface can;

} // namespace PUTM_CAN

#ifndef PUTM_USE_CAN_FD
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

#endif
