#include <cstdint>
#include <iostream>


#include "lib/can_interface.hpp"

// for testing
#include "hal_can.hpp"

// global created by CubeMX
CAN_HandleTypeDef hcan1;


void receive_example()
{
  // All is handeled in HAL_CAN_RxFifo0MsgPendingCallback in can_interface.hpp
  [[maybe_unused]]auto apps = PUTM_CAN::can.get_apps_main().pedal_position;
  [[maybe_unused]]auto counter = PUTM_CAN::can.get_apps_main().counter;

  [[maybe_unused]]auto active_current = PUTM_CAN::can.get_bms_hv_main().current;
  [[maybe_unused]]auto active_voltage = PUTM_CAN::can.get_bms_hv_main().voltage_sum;
  // and so on
}

void send_example()
{
  //  Always initialize an object
  // https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Res-always
  constexpr Apps_main apps_test{
    .pedal_position = 1200,
    .counter = 0,
    .position_diff = 0,
    .device_state = Apps_states::Normal_operation,
  };
  
  auto apps_main_frame = PUTM_CAN::Can_tx_message(apps_test, can_tx_header_APPS_MAIN);

  auto status = apps_main_frame.send(hcan1);
  if (HAL_StatusTypeDef::HAL_OK != status)
  {
    Error_Handler();
  };

}