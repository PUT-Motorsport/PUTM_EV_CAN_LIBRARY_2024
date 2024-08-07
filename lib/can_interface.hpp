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

#include "CanHeaders/PM09-CANBUS-AMK-FRONT-LEFT.hpp"
#include "CanHeaders/PM09-CANBUS-AMK-FRONT-RIGHT.hpp"
#include "CanHeaders/PM09-CANBUS-AMK-REAR-LEFT.hpp"
#include "CanHeaders/PM09-CANBUS-AMK-REAR-RIGHT.hpp"
#include "CanHeaders/PM09-CANBUS-BMS-HV.hpp"
#include "CanHeaders/PM09-CANBUS-BMS-LV.hpp"
#include "CanHeaders/PM09-CANBUS-DASHBOARD.hpp"
#include "CanHeaders/PM09-CANBUS-FRONTBOX.hpp"
#include "CanHeaders/PM09-CANBUS-REARBOX.hpp"
#include "CanHeaders/PM09_CANBUS_PC.hpp"

namespace PUTM_CAN {

class Can_interface {
    Device<DriverInput> driverInput{DRIVER_INPUT_CAN_ID};
    Device<Dashboard> dashboard{DASHBOARD_CAN_ID};

    Device<AmkFrontLeftActualValues1> amkFrontLeftActualValue1{FRONT_LEFT_AMK_ACTUAL_VALUES_1_CAN_ID};
    Device<AmkFrontRightActualValues1> amkFrontRightActualValues1{FRONT_RIGHT_AMK_ACTUAL_VALUES_1_CAN_ID};
    Device<AmkRearLeftActualValues1> amkRearLeftActualValue1{REAR_LEFT_AMK_ACTUAL_VALUES_1_CAN_ID};
    Device<AmkRearRightActualValues1> amkRearRightActualValues1{REAR_RIGHT_AMK_ACTUAL_VALUES_1_CAN_ID};

    Device<AmkFrontLeftSetpoints1> amkFrontLeftSetpoints{FRONT_LEFT_AMK_SETPOINTS_1_CAN_ID};
    Device<AmkFrontRightSetpoints1> amkFrontRightSetpoints{FRONT_RIGHT_AMK_SETPOINTS_1_CAN_ID};
    Device<AmkRearLeftSetpoints1> amkRearLeftSetpoints{REAR_LEFT_AMK_SETPOINTS_1_CAN_ID};
    Device<AmkRearRightSetpoints1> amkRearRightSetpoints{REAR_RIGHT_AMK_SETPOINTS_1_CAN_ID};

    Device<RearboxSafety> rearboxSafety{REARBOX_SAFETY_CAN_ID};
    Device<RearboxTemperature> rearboxTemperature{REARBOX_TEMPERATURE_CAN_ID};
    Device<RearboxMiscellaneous> rearboxMiscellaneous{REARBOX_MISCELLANEOUS_CAN_ID};

    Device<PcMainData> pcMainData{PC_MAIN_CAN_ID};
    Device<FrontData> frontData{FRONT_DATA_CAN_ID};
    Device<BMS_HV_main> bmsHv{BMS_HV_MAIN_CAN_ID};

    Device<BMS_LV_main> bmsLv{BMS_LV_MAIN_CAN_ID};
    Device<BMS_LV_temperature> bmsLvTemperature{BMS_LV_TEMPERATURE_CAN_ID};

    std::array<Device_base*, 40> device_array = {&driverInput,
                                                 &rearboxSafety,
                                                 &rearboxTemperature,
                                                 &rearboxMiscellaneous,
                                                 &dashboard,
                                                 &amkFrontLeftActualValue1,
                                                 &amkFrontRightActualValues1,
                                                 &amkRearLeftActualValue1,
                                                 &amkRearRightActualValues1,
                                                 &amkFrontLeftSetpoints,
                                                 &amkFrontRightSetpoints,
                                                 &amkRearLeftSetpoints,
                                                 &amkRearRightSetpoints,
                                                 &pcMainData,
                                                 &frontData,
                                                 &bmsHv,
                                                 &bmsLv,
                                                 &bmsLvTemperature};

  public:
    Can_interface() = default;

    bool parse_message(const Can_rx_message& m) {
        for(auto& device : device_array) {
            if(device->get_ID() == m.header.Identifier) {
                device->set_data(m);
                return true;
            }
        }

        return false;
    }

    DriverInput get_driver_input_main() { return driverInput.data; }

    RearboxSafety get_rearbox_safety() { return rearboxSafety.data; }

    RearboxTemperature get_rearbox_temperature() { return rearboxTemperature.data; }

    RearboxMiscellaneous get_rearbox_miscellaneous() { return rearboxMiscellaneous.data; }

    Dashboard get_dashboard() { return dashboard.data; }

    AmkFrontLeftActualValues1 get_amk_front_left_actual_values1() { return amkFrontLeftActualValue1.data; }
    AmkFrontLeftSetpoints1 get_amk_front_left_setpoints() { return amkFrontLeftSetpoints.data; }

    AmkFrontRightActualValues1 get_amk_front_right_actual_values1() { return amkFrontRightActualValues1.data; }

    AmkRearLeftActualValues1 get_amk_rear_left_actual_values1() { return amkRearLeftActualValue1.data; }
    AmkRearRightActualValues1 get_amk_rear_right_actual_values1() { return amkRearRightActualValues1.data; }

    PcMainData get_pc_main_data() { return pcMainData.data; }

    FrontData get_front_data_main_data() { return frontData.data; }

    BMS_HV_main get_bms_hv_main() { return bmsHv.data; }

    BMS_LV_main get_bms_lv_main() { return bmsLv.data; }

    BMS_LV_temperature get_bms_lv_temperature() { return bmsLvTemperature.data; }

    bool get_driver_input_main_new_data() { return driverInput.get_new_data(); }

    bool get_rearbox_safety_new_data() { return rearboxSafety.get_new_data(); }

    bool get_rearbox_temperature_new_data() { return rearboxTemperature.get_new_data(); }

    bool get_rearbox_miscellaneous_new_data() { return rearboxMiscellaneous.get_new_data(); }

    bool get_dashboard_new_data() { return dashboard.get_new_data(); }
    bool get_pc_new_data() { return pcMainData.get_new_data(); }

    bool get_front_data_main_new_data() { return frontData.get_new_data(); }
    bool get_amk_front_left_actual_values_new_data() { return amkFrontLeftActualValue1.get_new_data(); }

    bool get_bms_hv_main_new_data() { return bmsHv.get_new_data(); }

    bool get_bms_lv_main_new_data() { return bmsLv.get_new_data(); }

    bool get_bms_lv_temperature_new_data() { return bmsLvTemperature.get_new_data(); }
};

Can_interface can;

} // namespace PUTM_CAN

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef* hfdcan1, uint32_t RxFifo0ITs) {
    PUTM_CAN::Can_rx_message rx{*hfdcan1, 0};
    if(rx.status == HAL_StatusTypeDef::HAL_OK) {
        if(not PUTM_CAN::can.parse_message(rx)) {
            // Unknown message
            // Error_Handler();
        }
    }
}

#endif
