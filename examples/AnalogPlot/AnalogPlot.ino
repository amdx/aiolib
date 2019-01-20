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

// Read an analog value from P1, write its 10-bit value readout to the serial and
// show the PWM support for the onboard red LED
//
// For this example, connect:
//   * A potentiometer to P1. Wiper to P1, left pin to GND and right pin to 5V
//
// The values can be read either with Arduino's serial monitor
// or better with the serial plotter (Tools -> Serial plotter)

#include <Arduino.h>
// Always include the top level AIO header. It contains platform-specific pin assignments
#include <AIO.h>

// Every single bit in the library is declared inside the AIO namespace
using namespace AIO;

const uint16_t SAMPLE_PERIOD = 10;


void setup()
{
    // Initialize the USB serial port
    Serial.begin(115200);

    // Initialize AIO XL baseboard
    baseboard_init();
}

void loop()
{
    // Sample the voltage set to P1 via the potentiometer. ADC's resolution is 10 bits
    uint16_t adc_value = analogRead(P1);

    // Print the value to the serial. It'll be rendered as decimal value by default
    Serial.println(adc_value);

    // Set the onboard red led PWM to the adc value. We're shifting two bits here
    // since the PWM resolution for this pin is 8 bits
    analogWrite(LED_RED, adc_value >> 2);

    // Wait before repeating the cycle. This sets the sampling frequency of the plot
    delay(SAMPLE_PERIOD);
}
