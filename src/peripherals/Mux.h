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

// PCA9540B I2C mux

#ifndef MUH_H
#define MUX_H

#include <stdint.h>

namespace AIO {

class Mux {
public:
    typedef enum Channel {
        CHANNEL_NONE,
        CHANNEL_0,
        CHANNEL_1
    } Channel;

    Mux();

    void begin();
    void set_channel(Channel channel);

private:
    uint8_t read_mux();
    void write_mux(uint8_t data);
};

} // namespace AIO

#endif
