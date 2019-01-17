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

// Tests the onboard W5500 ethernet controller on the AIO XL

#include <Arduino.h>
#include <Ethernet.h>
#include <AIO.h>

using namespace AIO;

uint8_t mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
uint8_t analog_pins[] = {P1, P2, P3, P4, P5, P6, P7, P8};

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup()
{
    // Open serial communications and wait for port to open:
    Serial.begin(115200);

    Serial.print("Initializing..");

    Ethernet.init(ETH_CS_PIN);

    Ethernet.begin(mac, IPAddress(0, 0, 0, 0));
    Serial.println("done.");

    Serial.print("Waiting for link..");
    while (Ethernet.linkStatus() != LinkON) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("link is up.");
    Serial.print("Requesting IP via DHCP..");

    // start the Ethernet connection and the server:
    Ethernet.begin(mac);
    server.begin();
    Serial.println("done.");

    Serial.print("Connect to: http://");
    Serial.println(Ethernet.localIP());
}

void loop()
{
    // listen for incoming clients
    EthernetClient client = server.available();

    if (client) {
        Serial.println("new client");

        // an http request ends with a blank line
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                Serial.write(c);
                // if you've gotten to the end of the line (received a newline
                // character) and the line is blank, the http request has ended,
                // so you can send a reply
                if (c == '\n' && currentLineIsBlank) {
                    // send a standard http response header
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println("Connection: close"); // the connection will be closed after completion of the response
                    client.println("Refresh: 5"); // refresh the page automatically every 5 sec
                    client.println();
                    client.println("<!DOCTYPE HTML>");
                    client.println("<html>");
                    // output the value of each analog input pin
                    for (uint8_t channel_index = 0; channel_index < 8; ++channel_index) {
                        uint16_t adc_value = analogRead(analog_pins[channel_index]);

                        client.print("Analog input P");
                        client.print(channel_index + 1);
                        client.print(" = ");
                        client.print(adc_value);
                        client.println("<br />");
                    }
                    client.println("</html>");
                    break;
                }
                if (c == '\n') {
                    // you're starting a new line
                    currentLineIsBlank = true;
                } else if (c != '\r') {
                    // you've gotten a character on the current line
                    currentLineIsBlank = false;
                }
            }
        }
        // give the web browser time to receive the data
        delay(1);
        // close the connection:
        client.stop();
        Serial.println("client disconnected");
    }
}
