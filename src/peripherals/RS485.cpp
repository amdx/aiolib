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

#include <AIO.h>

#include "RS485.h"

namespace AIO {

namespace {
    const uint8_t RS485_DEFAULT_TX_EN_DELAY = 1; // [ms] time to enable (disable) transceiver before (after) sending

    HardwareSerial& serial = Serial1;
}

RS485::RS485(uint8_t config)
    : config_(config), txen_delay_(RS485_DEFAULT_TX_EN_DELAY)
{
}

void RS485::begin(uint32_t baud)
{
    pinMode(RS485_RX_EN_PIN, OUTPUT);
    digitalWrite(RS485_RX_EN_PIN, LOW);

    pinMode(RS485_TX_EN_PIN, OUTPUT);
    digitalWrite(RS485_TX_EN_PIN, LOW);

    serial.begin(baud, config_);
}

void RS485::begin(uint32_t baud, uint32_t timeout)
{
    begin(baud);
    serial.setTimeout(timeout);
}

void RS485::set_txen_delay(uint8_t txen_delay)
{
    txen_delay_ = txen_delay;
}

uint8_t RS485::read(uint8_t* dst_buf, uint8_t len)
{
    return serial.readBytes(dst_buf, len);
}

uint8_t RS485::write(const uint8_t* src_buf, uint8_t len)
{
    digitalWrite(RS485_TX_EN_PIN, HIGH);
    delay(txen_delay_);
    uint8_t num = serial.write(src_buf, len);
    serial.flush();
    delay(txen_delay_);
    digitalWrite(RS485_TX_EN_PIN, LOW);

    // discard sent bytes from RX buffer
    for (uint8_t i=0; i<len; i++) {
        while (!serial.available());
        serial.read();
    }

    return num;
}

} // namespace AIO
