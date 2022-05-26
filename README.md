# STM32_CAN_abstraction
C++ STM32 Hall CAN warper library

# Usage

The library constitutes of:

- `can_interface.hpp`, the main class responsible for receiving and interpreting frames
- a set of header files containing the structs that are relayed as frames' payloads.
- `message_abstraction.hpp`, a file handling the inner workings of the library

All files are automatically included once the `can_interface.hpp` is included.

**All classes, structs, enumeration types and constants are namespaced.**

# Inclusion requirements

(1) Can interrupt RX0 and RX1 must be enabled
(2) In properties->c/c++>build->includes add relative path to the library\
(3) Do `git submodule add -b <branch> <url> <relative_path_4m_root>` to add the library as a submodule
(4)

# Sending frames

To send a frame, first create a data structure that will be the frame's payload. All data structures are available once `can_interface.hpp` is included:

```c++
Apps_main apps_test{
    .pedal_position = 1200,
    .counter = 0,
    .position_diff = 0,
    .device_state = Apps_states::Normal_operation,
  };
```

Then, create a `PUTM_CAN::Can_tx_message` object. Its constructor takes the payload struct and `CAN_Tx_HeaderTypeDef` as arguments. Both are available in the CanHeaders and included with `can_interface.hpp`:

```c++
auto apps_main_frame = PUTM_CAN::Can_tx_message<Apps_main>(apps_test, can_tx_header_APPS_MAIN);
```

Finally, you can invoke the `send` method upon it. It takes the `CAN_HandleTypeDef`as an argument and will return a `Hal_StatusTypeDef`:

```c++
auto status = apps_main_frame.send(hcan1);
```

You can check if the frame was relayed correctly:

```c++
if (status != HAL_StatusTypeDef::HAL_OK) {}
```

# Receiving frames

The `can_interface.hpp` creates a **global** `PUTM_CAN::Can_interface can` object and registers a callback. The registered callback grants automatic frame interpretation into structs defined in the `CanHeaders/`. If an error is detected, it invokes the `Error_Handler()` function.

Since the frames are automatically interpreted, one can just invoke the proper getter method on the global `PUTM_Can::can` object to get one of the structs defined in `CanHeaders/`:

```c++
//example for bms_hv_main
auto bms = PUTM_CAN::can.get_bms_hv_main();
```

If you'd like to verify that the frame accessed is new, you can call functions such as `get_bms_hv_main_new_data()` that return a bool.

- all frames are zero-initialised
- a frame is not new until it has been received
- once a frame has been accessed, it is not new
