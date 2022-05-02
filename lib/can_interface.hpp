#ifndef CAN_INTERFACE_HPP
#define CAN_INTERFACE_HPP


#include <array>
#include <cstdint>
#include <stdio.h>

#include "stm32l4xx_hal.h"
#include "message_abstraction.hpp"

//CanHeaders
#include "CanHeaders/PM08-CANBUS-APPS.hpp"
#include "CanHeaders/PM08-CANBUS-AQ_CARD.hpp"
#include "CanHeaders/PM08-CANBUS-BMS_LV.hpp"
#include "CanHeaders/PM08-CANBUS-BMS_HV.hpp"
#include "CanHeaders/PM08-CANBUS-DASH.hpp"
#include "CanHeaders/PM08-CANBUS-LAP_TIMER.hpp"
#include "CanHeaders/PM08-CANBUS-SF.hpp"
#include "CanHeaders/PM08-CANBUS-STEERING_WHEEL.hpp"
#include "CanHeaders/PM08-CANBUS-TC.hpp"
#include "CanHeaders/PM08-CANBUS-TELEMETRY.hpp"

namespace new_can
{

  class Can_interface
  {

      Device<Apps_main> apps{ APPS_MAIN_CAN_ID };
      Device<AQ_main> aq_main{ AQ_MAIN_CAN_ID };
      Device<BMS_HV_main> bms_hv_main{ BMS_HV_MAIN_CAN_ID };
      Device<BMS_LV_main> bms_lv_main{ BMS_LV_MAIN_CAN_ID };
      Device<BMS_LV_temperature> bms_lv_temperature{ BMS_LV_TEMPERATURE_CAN_ID };
      Device<Dash_Main> dash_main{ DASH_MAIN_CAN_ID };
      Device<Dash_TCS> dash_TCS{ DASH_TCS_CAN_ID };
      Device<Dash_Smart_Fuses_FAN_speed> dash_fan_speed{ DASH_SMART_FUSES_FAN_SPEED_CAN_ID };
      Device<Lap_timer_Main> laptimer_main{ LAP_TIMER_MAIN_CAN_ID };
      Device<Lap_timer_Pass> laptimer_pass{ LAP_TIMER_PASS_CAN_ID };
      Device<SF_main> sf_main{ SF_MAIN_CAN_ID };
      Device<SF_FrontBox> sf_frontbox{ SF_FRONTBOX_CAN_ID };
      Device<SF_CoolingAndVSafety> sf_coolingandvsafety{ SF_COOLINGANDVSAFETY_CAN_ID };
      Device<SF_DV> sf_dv{ SF_DV_CAN_ID };
      Device<SF_WS> sf_ws{ SF_WS_CAN_ID};
      Device<SF_NUCS> sf_nucs{ SF_NUCS_CAN_ID };
      Device<Steering_Wheel_main> steering_wheel_main{ STEERING_WHEEL_MAIN_CAN_ID };
      Device<Steering_Wheel_event> steering_wheel_event{ STEERING_WHEEL_EVENT_CAN_ID };
      Device<TS_main> ts_main{ TS_MAIN_CAN_ID };
      Device<TS_rear_suspension> ts_rear_suspension{ TS_REAR_SUSPENSION_CAN_ID };
      Device<Telemetry_Main> telemetry_main{ TELEMETRY_MAIN_CAN_ID };

      std::array<Device_base*, 21> device_array = { &apps, &aq_main, &bms_hv_main,
                                          &bms_lv_main, &bms_lv_temperature, &dash_main, &dash_TCS, &dash_fan_speed,
                                          &laptimer_main, &laptimer_pass, &sf_main, &sf_frontbox, &sf_coolingandvsafety, 
                                          &sf_dv, &sf_ws, &sf_nucs, &steering_wheel_main, &steering_wheel_event,
                                          &ts_main, &ts_rear_suspension , &telemetry_main };

  public:
    Can_interface() = default;
    
    bool parse_message(const Can_rx_message &m)
    {
      for (auto &dev : device_array)
      {
        if (dev->IDE == m.header.IDE)
        {
          dev->set_data(m);
          return true; // to exit void
        }
      }
      return false;
    }

    const Apps_main& get_apps_main() { return apps.data; }
    const AQ_main& get_aq_main() { return aq_main.data; }
    const BMS_HV_main& get_bms_hv_main() { return bms_hv_main.data; }
    const BMS_LV_main& get_bms_lv_main() { return bms_lv_main.data; }
    const BMS_LV_temperature& get_bms_lv_temperature() { return bms_lv_temperature.data; }
    const Dash_Main& get_dash_main() { return dash_main.data; }
    const Dash_TCS_frame & get_dash_TCS() { return dash_TCS.data; }
    const Dash_Smart_Fuses_Fan_Speed& get_dash_fan_speed() { return dash_fan_speed.data; }
    const Lap_timer_Main& get_laptimer_main() { return laptimer_main.data; };
    const Lap_timer_Pass& get_laptimer_pass() { return laptimer_pass.data; }
    const SF_main& get_sf_main() { return sf_main.data; }
    const SF_FrontBox& get_sf_frontbox() { return sf_frontbox.data; }
    const SF_CoolingAndVSafety& get_sf_cooling() { return sf_coolingandvsafety.data; }
    const SF_DV& get_sf_dv() { return sf_dv.data; }
    const SF_WS& get_sf_ws() { return sf_ws.data; }
    const SF_NUCS& get_sf_nucs() { return sf_nucs.data; }
    const Steering_Wheel_main& get_steering_wheel_main() { return steering_wheel_main.data; }
    const Steering_Wheel_event& get_steering_wheel_event() { return steering_wheel_event.data; }
    const TS_main& get_tc_main() { return ts_main.data; }
    const TS_rear_suspension& get_tc_rear() { return ts_rear_suspension.data; }
    const Telemetry_Main& get_telemetry_main() { return telemetry_main.data; }
  };
} // namespace new_can

new_can::Can_interface can_interface;

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan){
	Can_rx_message rx{*hcan, 0};
	if (rx.status == HAL_StatusTypeDef::HAL_OK){
		can_interface.parse_message(rx);
	}
}


#endif
