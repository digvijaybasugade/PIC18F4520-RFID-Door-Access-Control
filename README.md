**RFID-Based Door Access Control System Using PIC18F4520**

This project implements an RFID-based access control system using the PIC18F4520 microcontroller, UART communication, a 4x3 keypad, and an LCD display. The system reads an RFID card ID through UART, verifies it against predefined authorized card IDs, and prompts the user to enter a PIN using the keypad. If both the RFID card and PIN are valid, access is granted and an LED is activated. The LCD displays system status messages such as card validation, password verification, and access granted or denied.

**Key Features:**
- RFID card identification and authentication
- UART serial communication
- Keypad-based PIN verification
- LCD status display
- LED indication for successful access
- Support for multiple authorized RFID cards

**Hardware:** PIC18F4520, RFID reader, 4x3 keypad, LCD, LED

**Programming Language:** Embedded C

**Development Environment:** MPLAB IDE / MPLAB X with a compatible PIC C compiler
