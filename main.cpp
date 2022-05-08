#include <catch2/catch_all.hpp>
#include <cstdint>
#include <iostream>

#include "hal_can.hpp"
#include "lib/can_interface.hpp"

// global created by CubeMX
CAN_HandleTypeDef hcan1;

template <typename T>
PUTM_CAN::Can_rx_message send_simulation(const PUTM_CAN::Can_tx_message<T> &tx) {
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

  const Apps_main apps_test{.pedal_position = 1200,
                            .counter = 12,
                            .position_diff = 2,
                            .device_state = Apps_states::Normal_operation};

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

TEST_CASE("Testing TS") {
  PUTM_CAN::Can_interface can;

  REQUIRE(can.get_tc_main().vehicle_speed == 0);
  REQUIRE(can.get_tc_main().water_temp == 0);
  REQUIRE(can.get_tc_main().water_pressure == 0);
  REQUIRE(can.get_tc_main().motor_current == 0);
  REQUIRE(can.get_tc_main().tractive_system_on == false);
  REQUIRE(can.get_tc_main().rtds_active == false);
  REQUIRE(can.get_tc_main().brake_light_active == false);
  REQUIRE(can.get_tc_main().traction_control_enable == false);
  REQUIRE(can.get_tc_main().regen_enable == false);
  REQUIRE(can.get_tc_main().regen_active == false);
  REQUIRE(can.get_tc_main().traction_control_intensivity == 0);
  REQUIRE(can.get_tc_main().device_state == TS_states::NORMAL_OPERATION);

  const TS_main tc_test{.vehicle_speed = 15000,
                        .water_temp = 24,
                        .water_pressure = 60,
                        .motor_current = 120,
                        .tractive_system_on = true,
                        .rtds_active = true,
                        .brake_light_active = true,
                        .traction_control_enable = true,
                        .regen_enable = true,
                        .regen_active = true,
                        .traction_control_intensivity = 7,
                        .device_state = TS_states::APPS_TIMEOUT};

  auto tx = PUTM_CAN::Can_tx_message(tc_test, can_tx_header_TS_MAIN);
  auto rx = send_simulation(tx);
  bool parsed = can.parse_message(rx);

  REQUIRE(parsed);

  auto tc = can.get_tc_main();
  REQUIRE(tc.vehicle_speed == tc_test.vehicle_speed);
  REQUIRE(tc.water_temp == tc_test.water_temp);
  REQUIRE(tc.water_pressure == tc_test.water_pressure);
  REQUIRE(tc.motor_current == tc_test.motor_current);
  REQUIRE(tc.tractive_system_on == tc_test.tractive_system_on);
  REQUIRE(tc.rtds_active == tc_test.rtds_active);
  REQUIRE(tc.brake_light_active == tc_test.brake_light_active);
  REQUIRE(tc.traction_control_enable == tc_test.traction_control_enable);
  REQUIRE(tc.regen_enable == tc_test.regen_enable);
  REQUIRE(tc.regen_active == tc_test.regen_active);
  REQUIRE(tc.traction_control_intensivity ==
          tc_test.traction_control_intensivity);
  REQUIRE(tc.device_state == tc_test.device_state);
}
