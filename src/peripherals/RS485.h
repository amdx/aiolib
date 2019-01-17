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

// MAX13442E RS485 transceiver

#ifndef RS485_H
#define RS485_H

#include <Arduino.h>

namespace AIO {

class RS485 {
public:
    RS485(uint8_t config=SERIAL_8N1);

    void begin(uint32_t baud);
    void begin(uint32_t baud, uint32_t timeout);
    void set_txen_delay(uint8_t txen_delay);

    uint8_t read(uint8_t* dst_buf, uint8_t len);
    uint8_t write(const uint8_t* src_buf, uint8_t len);

private:
    uint8_t config_;
    uint8_t txen_delay_;
};

} // namespace AIO

#endif
