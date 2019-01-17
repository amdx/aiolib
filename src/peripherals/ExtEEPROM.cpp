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

#include "ExtEEPROM.h"

namespace AIO {

namespace {
    const uint8_t I2C_ADDRESS = 0x50;
}

ExtEEPROM::ExtEEPROM()
{
}

uint8_t ExtEEPROM::read(uint16_t address)
{
    uint8_t value = 0xFF;

    Wire.beginTransmission(I2C_ADDRESS);
    Wire.write((int)(address >> 8));   // MSB
    Wire.write((int)(address & 0xFF)); // LSB
    Wire.endTransmission();

    Wire.requestFrom(I2C_ADDRESS, (uint8_t) 1);

    if (Wire.available()) {
        value = Wire.read();
    }

    return value;
}

uint8_t ExtEEPROM::read(uint32_t address)
{
    uint8_t value = 0xFF;

    Wire.beginTransmission( (uint8_t)(I2C_ADDRESS | ((address >> 16) & 0x03)));
    Wire.write((int)((address >> 8) & 0xFF));   // MSB
    Wire.write((int)(address & 0xFF)); // LSB
    Wire.endTransmission();

    Wire.requestFrom(I2C_ADDRESS, (uint8_t) 1);

    if (Wire.available()) {
        value = Wire.read();
    }
    return value;
}

void ExtEEPROM::write(uint16_t address, uint8_t value)
{
    Wire.beginTransmission(I2C_ADDRESS);
    Wire.write((int)(address >> 8));   // MSB
    Wire.write((int)(address & 0xFF)); // LSB
    Wire.write(value);
    Wire.endTransmission();

    // TODO: Really necessary?
    delay(5);
}

void ExtEEPROM::write(uint32_t address, uint8_t value)
{
    Wire.beginTransmission((uint8_t)(I2C_ADDRESS | ((address >> 16) & 0x03)));
    Wire.write((int)(address >> 8) & 0xFF);   // MSB
    Wire.write((int)(address & 0xFF)); // LSB
    Wire.write(value);
    Wire.endTransmission();

    // TODO: Really necessary?
    delay(5);
}

} // namespace AIO
