/**
 * AMDX AIO arduino library
 * 
 * Copyright (C) 2019 Archimedes Exhibitions GmbH
 * All rights reserved. 
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the "Software"), to deal in the Software 
 * without restriction, including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons
 * to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef AIO_H
#define AIO_H

// Note: these includes ensure a proper operation of platformio's LDF
#include <Wire.h>
#include <SPI.h>

namespace AIO {

#if defined(ARDUINO_AVR_PRO)

#define AIO_BOARD

const uint8_t P1 = 14;
const uint8_t P2 = 15;
const uint8_t P3 = 16;
const uint8_t P4 = 17;
const uint8_t P5 = 18;
const uint8_t P6 = 19;

const uint8_t X1 = 3;
const uint8_t X2 = 5;
const uint8_t X3 = 6;
const uint8_t X4 = 9;
const uint8_t X5 = 10;
const uint8_t X6 = 11;

const uint8_t LED_GREEN = 13;
const uint8_t LED_RED = 7;

#elif defined(ARDUINO_AVR_MEGA2560)

#define AIO_BOARD_XL

const uint8_t P1 = A15;
const uint8_t P2 = A14;
const uint8_t P3 = A13;
const uint8_t P4 = A12;
const uint8_t P5 = A11;
const uint8_t P6 = A10;
const uint8_t P7 = A9;
const uint8_t P8 = A8;

const uint8_t X1 = 6;
const uint8_t X2 = 7;
const uint8_t X3 = 8;
const uint8_t X4 = 9;
const uint8_t X5 = 10;
const uint8_t X6 = 44;
const uint8_t X7 = 45;
const uint8_t X8 = 46;

const uint8_t LED_GREEN = 13;
const uint8_t LED_RED = 12;
const uint8_t LED_BLUE = 11;

#define AIO_HAS_ETHERNET
const uint8_t ETH_CS_PIN = 23;
const uint8_t ETH_RST_PIN = 22;
const uint8_t ETH_NSOCKETS = 4;

#define AIO_HAS_RS485
const uint8_t RS485_RX_EN_PIN = 40; // active low
const uint8_t RS485_TX_EN_PIN = 41;

#else
#error Unable to detect AIO platform
#endif

void baseboard_init();

} // namespace AIO

#endif
