#include <cstdint>
#include <iostream>


#include "lib/can_interface.hpp"
#include "hal_can.hpp"

// global created by CubeMX
CAN_HandleTypeDef hcan1;

// TODO
// Create global can interface.
PUTM_CAN::Can_interface can;

void recive_example()
{
  // All is handeled in HAL_CAN_RxFifo0MsgPendingCallback in can_interface.hpp
  [[maybe_unused]]auto apps = can.get_apps_main().pedal_position;
  [[maybe_unused]]auto counter = can.get_apps_main().counter;

  [[maybe_unused]]auto active_current = can.get_bms_hv_main().current;
  [[maybe_unused]]auto active_voltage = can.get_bms_hv_main().voltage_sum;
  // and so on
}

void send_example()
{
  //  Always initialize an object
  // https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Res-always
  Apps_main apps_test{
    .pedal_position = 1200,
    .counter = 0,
    .position_diff = 0,
    .device_state = Apps_states::Normal_operation,
  };

  // Seperate message and send method allows for compile time messages array creation.
  auto apps_main_frame = PUTM_CAN::Can_tx_message(apps_test, can_tx_header_APPS_MAIN);

  auto status = apps_main_frame.send(hcan1);
  if (HAL_StatusTypeDef::HAL_OK != status)
  {
    Error_Handler();
  };

}

void test_case_can_tx_message()
{
  Apps_main apps_test;
  apps_test.pedal_position = 1300;
  apps_test.counter = 12;
  apps_test.device_state = Apps_states::Normal_operation;


  // example sending senario
  auto tx = PUTM_CAN::Can_tx_message(apps_test, can_tx_header_APPS_MAIN);
  auto res = tx.send(hcan1);
  if (res != HAL_StatusTypeDef::HAL_OK)
  {
    // Error_Handler("CAN sending error");
  };

  // copy tx to rx (CAN simulation)
  PUTM_CAN::Can_rx_message rx(hcan1, 1);
  std::copy(tx.buff, tx.buff + sizeof(Apps_main), rx.data);

  // print rx buffor
  printf("\nbuffor: ");
  for (std::size_t i = 0; i < sizeof(Apps_main); ++i)
  {
    printf(" %d", (int)rx.data[i]);
  }
  // CAN recive data
  can.parse_message(rx);
}

int main()
{
  std::cout << "size of Device base " << sizeof(PUTM_CAN::Can_interface) << std::endl;
  test_case_can_tx_message();
}
