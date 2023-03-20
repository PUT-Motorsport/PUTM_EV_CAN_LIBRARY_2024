#include "library.hpp"

#include "CanHeaders/PM08-CANBUS-AQ_CARD.hpp"
#include "CanHeaders/PM08-CANBUS-BMS_HV.hpp"
#include "CanHeaders/PM08-CANBUS-BMS_LV.hpp"
#include "CanHeaders/PM08-CANBUS-DASH.hpp"
#include "CanHeaders/PM08-CANBUS-DV.hpp"
#include "CanHeaders/PM08-CANBUS-LAP_TIMER.hpp"
#include "CanHeaders/PM08-CANBUS-SF.hpp"
#include "CanHeaders/PM08-CANBUS-STEERING_WHEEL.hpp"
#include "CanHeaders/PM08-CANBUS-SW_SENSOR.hpp"
#include "CanHeaders/PM08-CANBUS-TC.hpp"
#include "CanHeaders/PM08-CANBUS-TELEMETRY.hpp"
#include "CanHeaders/PM08-CANBUS-WHEELTEMP.hpp"
#include "CanHeaders/PM08-CANBUS-YAWPROBE.hpp"
#include "meta.hpp"

#include "CanHeaders/can_headers.hpp"

#include <array>
#include <cstring> // memcpy
#include <cassert>
#include <limits>
#include "can.hpp"

namespace {
struct ParsedMessage {
  const PUTM_CAN::can_id_t id;
  uint8_t data[PUTM_CAN::MAX_MESSAGE_SIZE];
};

#define MSG(x) ParsedMessage{PUTM_CAN::frame_id<x>, 0}

// this array is created to allow static_assert that each frame is filled correctly
constexpr std::array<ParsedMessage, PUTM_CAN::NUM_PARSED_MSG> __messages {
    MSG(PUTM_CAN::Apps_main),
    MSG(PUTM_CAN::AQ_main),
    MSG(PUTM_CAN::AQ_acceleration),
    MSG(PUTM_CAN::AQ_gyroscope),
    MSG(PUTM_CAN::AQ_ts_button),
    MSG(PUTM_CAN::BMS_HV_main),
    MSG(PUTM_CAN::BMS_LV_main),
    MSG(PUTM_CAN::BMS_LV_temperature),
    MSG(PUTM_CAN::Dash_Main),
    MSG(PUTM_CAN::DV_Ass),
    MSG(PUTM_CAN::Lap_timer_Main),
    MSG(PUTM_CAN::Lap_timer_Sector),
    MSG(PUTM_CAN::Lap_timer_Acc_time),
    MSG(PUTM_CAN::Lap_timer_Skidpad_time),
    MSG(PUTM_CAN::Lap_timer_Lap_time),
    MSG(PUTM_CAN::SF_main),
    MSG(PUTM_CAN::SF_PassiveElements),
    MSG(PUTM_CAN::SF_LegendaryDVAndSupply),
    MSG(PUTM_CAN::SF_Supply),
    MSG(PUTM_CAN::SF_safety),
    MSG(PUTM_CAN::Steering_Wheel_main),
    MSG(PUTM_CAN::Steering_Wheel_event),
    MSG(PUTM_CAN::SWPS_main),
    MSG(PUTM_CAN::TC_main),
    MSG(PUTM_CAN::TC_rear_suspension),
    MSG(PUTM_CAN::TC_wheel_velocities),
    MSG(PUTM_CAN::TC_temperatures),
    MSG(PUTM_CAN::TC_imu_gyro),
    MSG(PUTM_CAN::TC_imu_acc),
    MSG(PUTM_CAN::Telemetry_Main),
    MSG(PUTM_CAN::WheelTemp_main),
    MSG(PUTM_CAN::YawProbe_air_flow),
};

std::array<ParsedMessage, PUTM_CAN::NUM_PARSED_MSG> messages{__messages};

constexpr std::size_t invalid_frame_id{std::numeric_limits<std::size_t>::max()};

template<typename frame_t>
constexpr std::size_t frame_index{invalid_frame_id};

#define DECL_INDEX(x, index) template<> constexpr std::size_t frame_index<x>{index}

DECL_INDEX(PUTM_CAN::Apps_main, 0);
DECL_INDEX(PUTM_CAN::AQ_main, 1);
DECL_INDEX(PUTM_CAN::AQ_acceleration, 2);
DECL_INDEX(PUTM_CAN::AQ_gyroscope, 3);
DECL_INDEX(PUTM_CAN::AQ_ts_button, 4);
DECL_INDEX(PUTM_CAN::BMS_HV_main, 5);
DECL_INDEX(PUTM_CAN::BMS_LV_main, 6);
DECL_INDEX(PUTM_CAN::BMS_LV_temperature, 7);
DECL_INDEX(PUTM_CAN::Dash_Main, 8);
DECL_INDEX(PUTM_CAN::DV_Ass, 9);
DECL_INDEX(PUTM_CAN::Lap_timer_Main, 10);
DECL_INDEX(PUTM_CAN::Lap_timer_Sector, 11);
DECL_INDEX(PUTM_CAN::Lap_timer_Acc_time, 12);
DECL_INDEX(PUTM_CAN::Lap_timer_Skidpad_time, 13);
DECL_INDEX(PUTM_CAN::Lap_timer_Lap_time, 14);
DECL_INDEX(PUTM_CAN::SF_main, 15);
DECL_INDEX(PUTM_CAN::SF_PassiveElements, 16);
DECL_INDEX(PUTM_CAN::SF_LegendaryDVAndSupply, 17);
DECL_INDEX(PUTM_CAN::SF_Supply, 18);
DECL_INDEX(PUTM_CAN::SF_safety, 19);
DECL_INDEX(PUTM_CAN::Steering_Wheel_main, 20);
DECL_INDEX(PUTM_CAN::Steering_Wheel_event, 21);
DECL_INDEX(PUTM_CAN::SWPS_main, 22);
DECL_INDEX(PUTM_CAN::TC_main, 23);
DECL_INDEX(PUTM_CAN::TC_rear_suspension, 24);
DECL_INDEX(PUTM_CAN::TC_wheel_velocities, 25);
DECL_INDEX(PUTM_CAN::TC_temperatures, 26);
DECL_INDEX(PUTM_CAN::TC_imu_gyro, 27);
DECL_INDEX(PUTM_CAN::TC_imu_acc, 28);
DECL_INDEX(PUTM_CAN::Telemetry_Main, 29);
DECL_INDEX(PUTM_CAN::WheelTemp_main, 30);
DECL_INDEX(PUTM_CAN::YawProbe_air_flow, 31);

} // namespace

template<typename frame_t>
frame_t get() noexcept {
    static_assert(PUTM_CAN::frame_id<frame_t> not_eq invalid_frame_id, "get() called on a wrong type");
    static_assert(__messages.at(frame_index<frame_t>.id) == PUTM_CAN::frame_id<frame_t>, "Wrong frame initialization");
    return *reinterpret_cast<frame_t*>(messages.at(frame_index<frame_t>).data);
}

static void parse(PUTM_CAN::can_id_t received_id, std::size_t received_length, uint8_t const *data) {
    for (auto& msg: messages) {
        if (msg.id == received_id) {
            std::memcpy(&msg.data, data, received_length);
            return; // binary search???
        };
    }
    // error handling?
}
