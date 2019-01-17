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

#ifndef B42_H
#define B42_H

#include <Arduino.h>


#define B42_DEFAULT_SERIAL_SPEED    115200
#define B42_MAX_COMMANDS            16
#define B42_MAX_DATA_LENGTH         3

#define B42_ERROR_NONE            0x00
// protocol errors
#define B42_ERROR_ZERO_BYTE       0x01
#define B42_ERROR_EXPECT_COMMAND  0x02
#define B42_ERROR_EXPECT_DATA1    0x03
#define B42_ERROR_EXPECT_DATA2    0x04
#define B42_ERROR_EXPECT_DATA3    0x05
// command processing errors
#define B42_ERROR_INVALID_COMMAND 0x10
// feature not yet implemented
#define B42_ERROR_NOT_IMPLEMENTED 0x3F


typedef uint8_t B42ReturnCode;
typedef B42ReturnCode (*CommandHandlerPtr)(uint8_t dataLen, uint8_t* data);
typedef void (*ErrorHandlerPtr)(B42ReturnCode rc);

typedef struct B42FrameBuffer
{
    uint8_t command;
    uint8_t dataLen;
    uint8_t data[B42_MAX_DATA_LENGTH];
} B42FrameBuffer;

class B42
{
public:
    B42();
    void begin();
    void begin(Stream &commStream);
    void update();
    void registerCommandHandler(uint8_t command, CommandHandlerPtr handler);
    void setErrorHandler(ErrorHandlerPtr handler);
    void sendFrame(uint8_t command, uint8_t dataLen, uint8_t* data);

private:
    CommandHandlerPtr m_cmdHandlers[B42_MAX_COMMANDS];
    ErrorHandlerPtr m_errorHandler;
    B42FrameBuffer m_frameBuffer;
    Stream *m_commStream;
    uint8_t m_expectedFrameSeq;

    void parseFrame();
    void reportError(B42ReturnCode rc);
};

extern B42 b42;

#endif
