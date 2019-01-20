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

// Copy the state of P1 (eg: button) to P8 (eg: LED)
// For this example, connect:
//   * A button or switch between P1 and GND
//   * An LED (with a limiting resistor of at least 470Ohm) between P8 and GND or 5V

#include <Arduino.h>
// Always include the top level AIO header. It contains platform-specific pin assignments
#include <AIO.h>

// Every single bit in the library is declared inside the AIO namespace
using namespace AIO;


void setup()
{
    baseboard_init();

    // Set up P1 as input and attach an internal weak pullup to it, so
    // it won't float
    pinMode(P1, INPUT_PULLUP);
    
    // Set up P8 as output
    pinMode(P8, OUTPUT);
}

void loop()
{
    // Copy the state of P1 (inverted, since the button will short P1 to ground)
    // to P8
    digitalWrite(P8, !digitalRead(P1));

    // Do the same with the internal red LED
    digitalWrite(LED_RED, !digitalRead(P1));
}
