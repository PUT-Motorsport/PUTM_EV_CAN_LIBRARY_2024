# STM32_CAN_abstraction
C++ STM32 Hall CAN warper library

# Changes

## Breaking changes

### CAN and CANFD classes

Classes for messages are replaced with CAN and CANFD, encapsulating the bus. The public API doesn't offer any abstraction over data structures sent on the bus.

Those classes may co-exist as they do not share any data. **Frames receipt and parsing will be handled separately, no matter which bus the frame was read from.**

#### Uniform initialization
This allows for the library itself to perform full CAN initialization. Instantiating a CAN/CANFD class consumes the pointer to peripheral.

#### Opt-in behind the scenes reinitialization

??? This is wip

The CAN/CANFD classes will perform on-error reinitialization of the underlying peripherals. There will be a possibility to statically opt-in for this feature.

## But...

The CAN/CANFD constructor error handling will call `Error_Handler`, so that these objects cannot exist in an erroneous state. Also, if the class will not be able to "revive" the connection, `Error_Handler` will be called.

## Changes
### Context-aware sending and receiving

The library automatically chooses the right ID for the data structure that is passed. Moreover, through the use of templates, there is one function to write and read from the bus:

```c++
template <typename frame_t> 
bool send(frame_t const &frame) noexcept;
template<typename frame_t>
frame_t get() noexcept;
```

### CAN/CANFD filter helpers

Handle the black-magic inner workings of filters behind an API.

```c++
constexpr CAN_FilterTypeDef id(can_id_t id1, can_id_t id2) noexcept;
constexpr CAN_FilterTypeDef mask(uint32_t mask, can_id_t filter) noexcept;
```

Also, 'null filter' compile time constant
```c++
constexpr CAN_FilterTypeDef null_filter;
```

#### How the filter works in MASK mode

```c++
if ((filter_mask & message_id) == (filter_mask & filter_identifier)) {
    // accept frame
} else {
    // reject frame
}
```

#### How the filter works in ID mode
```c++
if ((message_id == filter_id_1) or (message_id == filter_id_2)) {
    // accept frame
} else {
    // reject frame
}
```