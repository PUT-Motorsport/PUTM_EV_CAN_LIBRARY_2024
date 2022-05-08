#include <catch2/catch_all.hpp>
#include <iostream>
#include <cstdint>

#include "lib/can_interface.hpp"
#include "hal_can.hpp"

// global created by CubeMX
CAN_HandleTypeDef hcan1;

template <typename T>
PUTM_CAN::Can_rx_message send_simulation(const PUTM_CAN::Can_tx_message<T> &tx)
{
  PUTM_CAN::Can_rx_message rx(hcan1, 1);
  rx.header.IDE = tx.header.IDE;
  rx.header.DLC = tx.header.DLC;
  rx.header.StdId = tx.header.StdId;
  rx.header.ExtId = tx.header.ExtId;
  rx.header.RTR = tx.header.RTR;
  std::copy(tx.buff, tx.buff + sizeof(T), rx.data);
  return rx;
}

TEST_CASE("Testing apps") {

  PUTM_CAN::Can_interface can;

  REQUIRE(can.get_apps_main().pedal_position == 0);
  REQUIRE(can.get_apps_main().counter == 0);
  REQUIRE(can.get_apps_main().position_diff == 0);
  REQUIRE(can.get_apps_main().device_state == Apps_states::Normal_operation);

  Apps_main apps_test{
    .pedal_position = 1200,
    .counter = 4,
    .position_diff = 2,
    .device_state = Apps_states::Normal_operation
  };
  
  auto tx = PUTM_CAN::Can_tx_message(apps_test, can_tx_header_APPS_MAIN);

  auto rx = send_simulation(tx);

  bool parsed = can.parse_message(rx);

  REQUIRE(parsed);

  auto apps = can.get_apps_main();  

  // require all fields of apps are equal to apps_test
  REQUIRE(apps.counter == apps_test.counter);
  REQUIRE(apps.pedal_position == apps_test.pedal_position);
  REQUIRE(apps.position_diff == apps_test.position_diff);
  REQUIRE(apps.device_state == apps_test.device_state);
}


