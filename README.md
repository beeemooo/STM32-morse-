# 🔤 STM32 Morse Code via UART

This project implements a Morse code transmitter using STM32 microcontroller, UART interrupt mechanism, and LED signal output. The system converts input text from the PC terminal into Morse code, and then generates LED blinking patterns according to Morse timing specifications.

>  This project demonstrates UART communication, ring buffer management, and real-time Morse code interpretation using embedded C.

---

## 📦 Features

- **UART RX/TX interrupt-based communication**
- **Ring buffer implementation** for both UART and Morse code processing
- **Character-to-Morse Lookup Table** for easy expansion and debugging
- **Precise Morse timing control** (1-unit, 3-unit, 7-unit delay scheme)
- Terminal feedback: `Processing morse code...` and `DONE` message
- **Debug print support** and waveform generation with Python plotting

---

##  System Architecture

```plaintext
+-----------------+      +--------------------+       +---------------------+
|   PC Terminal   | <--> |   UART Processing  | <-->  |   Morse Processor   |
| (TeraTerm etc.) |      |  RX/TX Interrupts  |       |  Lookup + LED Ctrl  |
+-----------------+      +--------------------+       +---------------------+
                                 ↑
                       Ring Buffers (128 bytes each)

