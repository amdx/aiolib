/**
 * AMDX AIO arduino library
 *
 * Copyright (C) 2019-2020 Archimedes Exhibitions GmbH
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

// A simple DMX sender example.
// Connect the DMX receiver to the mini-IO port (RS485 A/B and GND)
// The brightness value increases up to 255 and then restarts from 0.
// The brightness value is send to all DMX channels.

#include <Arduino.h>
#include <AIO.h>
#include <DmxSimple.h>

using namespace AIO;

const uint8_t DMX_TX_PIN = 18;
const uint8_t RS485_DE_ENABLE = 41;

const uint16_t NUM_DMX_CHANNELS = 512;
const uint8_t BRIGHTNESS_UPDATE_DELAY = 20;

void setup()
{
    // set the RS485_DE pin to HIGH in order to enable transmission
    pinMode(RS485_DE_ENABLE, OUTPUT);
    digitalWrite(RS485_DE_ENABLE, HIGH);

    // define the DMX TX pin to be used
    DmxSimple.usePin(DMX_TX_PIN);
    // set the number of DMX channels to be used
    DmxSimple.maxChannel(NUM_DMX_CHANNELS);
}

void loop()
{
    static uint8_t brightness = 0;

    for (uint16_t i=0 ; i<NUM_DMX_CHANNELS; ++i) {
        // update the DMX packet
        DmxSimple.write(i, brightness);
    }
    ++brightness;   // increase brightness

    delay(BRIGHTNESS_UPDATE_DELAY);
}
