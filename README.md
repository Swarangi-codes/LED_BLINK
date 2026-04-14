# LED Blink using AVR (ATmega328P)

## Overview
This project demonstrates a minimal bare-metal implementation of an LED blinking application on the **ATmega328P** microcontroller using direct register manipulation in C.

The program configures a GPIO pin as output and toggles it with a software delay loop, creating a visible blinking effect.

---

## Features
- Direct register-level programming (no Arduino libraries)
- Lightweight and efficient (`-Os` optimization)
- Demonstrates GPIO control and timing using delay loops
- Compatible with standard AVR toolchain (`avr-gcc`, `avrdude`)

---

## Hardware Requirements
- ATmega328P microcontroller (e.g., Arduino Uno)
- LED connected to **PORTB5** (Digital Pin 13 on Arduino Uno)
- Current limiting resistor (~220Ω)
- USB connection for flashing

---

## Code Explanation

### Register Definitions
```c
#define PORTB *(volatile uint8_t*)0x25
#define DDRB  *(volatile uint8_t*)0x24
```

- DDRB: Data Direction Register (1 = output, 0 = input)
- PORTB: Output register for PORTB pins

### Main Logic
```c
DDRB |= (1<<5);
```
- Sets PB5 as output.
```c
PORTB |= (1<<5);   // LED ON
PORTB &= ~(1<<5);  // LED OFF
```
- Delay Mechanism
```c
for(i = 0; i < 0x7D00; i++);
```
- Simple busy-wait loop
- Approximate delay depends on CPU clock frequency

---
## Build and Flash Instructions

 1. Compile the Code
 ```bash
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o led.o led.c
 ```
 2. Link the Object File
 ```bash
 avr-gcc -o led.bin led.o
 ```
 3. Generate HEX File
 ```bash
avr-objcopy -O ihex -R .eeprom led.bin led.hex
 ```
 4. Flash to Microcontroller
 ```bash
sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:led.hex
 ```

 ---

## Notes
- The delay loop is not precise and varies with compiler optimizations and clock frequency.
- For accurate timing, consider using hardware timers instead of software delays.
- Ensure correct port (/dev/ttyACM0) based on your system configuration.
---

## Project Structure
```c
.
├── led.c        # Source code
├── led.o        # Object file (generated)
├── led.bin      # Binary file (generated)
├── led.hex      # Flashable HEX file (generated)
└── README.md    # Documentation
```
---
## Future Improvements
- Replace delay loop with timer-based interrupt
- Add configurable blink frequency
- Extend to multiple LEDs or patterns
---
## LICENSE

This version is **GitHub-ready**, renders correctly, and avoids any formatting issues.