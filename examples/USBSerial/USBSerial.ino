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

// Explore the basic functionalities of the onboard USB Serial port

#include <Arduino.h>
// Always include the top level AIO header. It contains platform-specific pin assignments
#include <AIO.h>

// Every single bit in the library is declared inside the AIO namespace
using namespace AIO;


void setup()
{
    // Initialize the serial port at 115200bps. "Serial" is bound to the pin pair
    // TXD0/RXD0, connected to the USB bridge.
    Serial.begin(115200);

    // Initialize AIO XL baseboard
    baseboard_init();

    // Print a line of text. This will be shown when the terminal connects to the
    // USB ACM serial port (provided that the board is being reset)
    Serial.println("Helloworld! Whatever you type it will be echoed back");
}

void loop()
{
    // Simply echo each incoming character back
    while (Serial.available()) {
        Serial.write(Serial.read());
    }
}
