#ifndef MESSAGE_ABSTRACTION_H
#define MESSAGE_ABSTRACTION_H

#include "stm32l4xx_hal.h"
#include <cstdint>
#include <cstring>

static const std::size_t max_dlc_size = 8;

struct Can_rx_message
{
  Can_rx_message(CAN_HandleTypeDef &hcan, uint32_t RxFifo)
      : header{}, data{0}
  {
    this->status =
        HAL_CAN_GetRxMessage(&hcan, RxFifo, &this->header, this->data);
  }

  CAN_RxHeaderTypeDef header;
  uint8_t data[max_dlc_size];
  HAL_StatusTypeDef status;
};

template <typename T>
struct Can_tx_message
{
  Can_tx_message(const T &data, const CAN_TxHeaderTypeDef &message_header)
      : header{message_header}
  {
    static_assert(std::is_trivially_constructible<T>(),
                  "Object must by C like struct");
    static_assert(std::is_class<T>(), "Object must by C like struct");
    std::memcpy(this->buff, &data, sizeof(T));
  }

  uint8_t buff[max_dlc_size];
  CAN_TxHeaderTypeDef header;

  HAL_StatusTypeDef send(CAN_HandleTypeDef &hcan)
  {
	static constexpr uint32_t TxMailbox{0};
    return HAL_CAN_AddTxMessage(&hcan, &this->header, this->buff, const_cast<uint32_t*>(&TxMailbox));
  }
};

class Device_base
{
public:
  const uint32_t IDE;
  const uint32_t DLC;
  bool new_data;
  constexpr Device_base(uint32_t ide, uint32_t dlc) : IDE{ide}, DLC{dlc}, new_data{false} {}
  virtual void set_data(const Can_rx_message &m) = 0;

  [[nodiscard]] bool get_new_data(){
    auto temp = new_data;
    new_data = false;
    return temp;
  }

};

template <typename T>
class Device : public Device_base
{
public:
  explicit constexpr Device(uint32_t ide)
      : Device_base(ide, sizeof(T)){};

  T data{};

  void set_data(const Can_rx_message &m) override
  {
    new_data = true;
    std::memcpy(&data, m.data, sizeof(T));
  }
};


#endif
