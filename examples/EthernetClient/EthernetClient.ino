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

const uint8_t MAX_CHUNK_SIZE = 128;

uint8_t mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

EthernetClient client;

void fetch_page(const char* host)
{
    uint8_t chunk[MAX_CHUNK_SIZE];

    Serial.print(F(">>> Connecting to: "));
    Serial.println(host);

    if (client.connect(host, 80)) {
        client.write("HEAD / HTTP/1.1\nHost:");
        client.write(host);
        client.write("\nConnection: close\n\n");

        Serial.println(F(">>> Retrieving data:"));

        while (1) {
            int length = client.read(chunk, MAX_CHUNK_SIZE);
            if (length > 0) {
                Serial.write(chunk, length);
            } else if (!client.connected()) {
                Serial.println();
                Serial.println(F(">>> Head fetched"));
                break;
            }
        }
    } else {
        Serial.println(F("*** Cannot connect to the remote end"));
    }
}

void setup()
{
    // Open serial communications and wait for port to open:
    Serial.begin(115200);

    Serial.print(F("Initializing.."));

    Ethernet.init(ETH_CS_PIN);

    Ethernet.begin(mac, IPAddress(0, 0, 0, 0));
    Serial.println("done.");

    Serial.print(F("Waiting for link.."));
    while (Ethernet.linkStatus() != LinkON) {
        delay(500);
        Serial.print(".");
    }

    Serial.println(F("link is up."));
    Serial.print(F("Requesting IP via DHCP.."));

    // Initialize the ethernet library
    Ethernet.begin(mac);
    Serial.println(F("done."));
    
    fetch_page("www.google.com");
}

void loop()
{
}
