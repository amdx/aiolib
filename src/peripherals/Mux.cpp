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

#include <Arduino.h>
#include <Wire.h>

#include "Mux.h"

namespace AIO {

namespace {
    const uint8_t I2C_ADDRESS = 0x70;

    const uint8_t CHANNEL_NONE_SELECT = 0;
    const uint8_t CHANNEL_0_SELECT = 0x04;
    const uint8_t CHANNEL_1_SELECT = 0x05;
}

Mux::Mux()
{
}

void Mux::begin()
{
    Wire.begin();
}

void Mux::set_channel(Channel channel)
{
    switch (channel) {
        case CHANNEL_NONE:
            write_mux(CHANNEL_NONE_SELECT);
            break;

        case CHANNEL_0:
            write_mux(CHANNEL_0_SELECT);
            break;

        case CHANNEL_1:
            write_mux(CHANNEL_1_SELECT);
            break;

        default:
            break;
    }
}

uint8_t Mux::read_mux()
{
    Wire.beginTransmission(I2C_ADDRESS);
    Wire.endTransmission();
    Wire.requestFrom(I2C_ADDRESS, (uint8_t) 1);
    return Wire.read();
}

void Mux::write_mux(uint8_t data)
{
    Wire.beginTransmission(I2C_ADDRESS);
    Wire.write(data);
    Wire.endTransmission();
}

} // namespace AIO
