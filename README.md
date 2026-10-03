# Week 2 - Firmware Development and Implementation

## Application
Timer-Based LED Controller with UART Communication

## Objective
The firmware demonstrates GPIO control, timer interrupts, UART communication,
debugging, testing and basic embedded-code documentation.

## Features
- LED ON/OFF control through UART.
- Automatic LED blinking using a periodic timer.
- Timer interrupt used as the system time base.
- UART status message and simple command interface.
- Short interrupt service routine with application processing in the main loop.

## Firmware Architecture
The application is organized into:
1. GPIO/LED control
2. 1 ms timer time base
3. Timer interrupt service routine
4. UART communication
5. UART command processing
6. Main application loop

## UART Settings
- Baud rate: 115200
- Data bits: 8
- Parity: None
- Stop bits: 1
- Flow control: None

## Commands
- `1` : LED ON
- `0` : LED OFF
- `A` or `a` : Automatic blinking mode
- `S` or `s` : Print firmware status

## Timer Operation
A 1 ms timer time base is used. In automatic mode, the LED state is
toggled every 500 ms.

## Build / Run
1. Create a project for the selected microcontroller or embedded simulator.
2. Add `main.c` to the project.
3. Map the GPIO, timer and UART abstraction functions to the board/SDK.
4. Configure UART as 115200, 8-N-1.
5. Build/compile the project.
6. Flash the firmware or start the simulator.
7. Open a serial terminal with the same UART settings.
8. Send the commands listed above.
9. Compare the observed behavior with the testing checklist.

## Testing
The firmware should be tested in the following order:
1. GPIO/LED test.
2. Timer interrupt test.
3. UART transmit test.
4. UART receive/command test.
5. Automatic blinking test.
6. Reset/reinitialization test.
7. Longer-duration stability test.

### Expected Test Checks
- Command `1` should turn the LED ON.
- Command `0` should turn the LED OFF.
- Command `A` should enable automatic blinking.
- Command `S` should return a firmware status message.
- The firmware should start with the LED in the OFF state.

Actual hardware/simulator observations should be recorded after execution.

## Important Functions
- `timer_isr()` - records periodic timer events.
- `process_command()` - handles UART commands.
- `send_status()` - sends a diagnostic message.
- `main()` - initializes peripherals and executes the event loop.

## Project Structure
```text
week2-firmware-development/
├── main.c
└── README.md
```

## Code Quality Practices
- Meaningful variable and function names are used.
- Inline comments explain important firmware operations.
- The interrupt service routine is kept short.
- Application processing is handled in the main loop.
- Hardware-dependent functions are separated through abstraction prototypes.

## Limitation
The low-level hardware functions are intentionally abstract because the
internship task does not specify a particular microcontroller or development
board. These functions must be mapped to the selected MCU/SDK before compiling
on real hardware.

## Possible Improvements
- Add a hardware-specific driver layer.
- Add UART error handling.
- Add command validation and acknowledgements for invalid commands.
- Add configurable blink timing.
- Add watchdog protection.
- Add unit tests for command processing.
