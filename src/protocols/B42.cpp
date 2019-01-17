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

#include "B42.h"

B42::B42()
{
    m_errorHandler = NULL;
    m_expectedFrameSeq = 0;
    memset(m_cmdHandlers, 0, sizeof(m_cmdHandlers));
}

void B42::begin()
{
    Serial.begin(B42_DEFAULT_SERIAL_SPEED);
    begin(Serial);
}

void B42::begin(Stream &commStream)
{
    m_commStream = &commStream;
}

void B42::update()
{
    while (m_commStream->available()) {
        uint8_t inByte = m_commStream->read();
        uint8_t frameSeq = inByte >> 6;

        if (inByte == 0) {
            reportError(B42_ERROR_ZERO_BYTE);
            m_expectedFrameSeq = 0;
            continue;
        } else if (m_expectedFrameSeq != frameSeq) {
            reportError(B42_ERROR_EXPECT_COMMAND + m_expectedFrameSeq);
            m_expectedFrameSeq = 0;
            continue;
        }

        if (frameSeq == 0) {
            m_frameBuffer.command = inByte & 0x0f;
            m_frameBuffer.dataLen = (inByte >> 4) & 0x03;
            if (m_frameBuffer.dataLen > 0) {
                ++m_expectedFrameSeq;
            }
        } else {
            m_frameBuffer.data[frameSeq-1] = inByte & 0x3f;
            ++m_expectedFrameSeq;
        }

        if (frameSeq == m_frameBuffer.dataLen) {
            parseFrame();
            m_expectedFrameSeq = 0;
        }
    }
}

void B42::parseFrame()
{
    if (m_cmdHandlers[m_frameBuffer.command]) {
        B42ReturnCode rc = m_cmdHandlers[m_frameBuffer.command](m_frameBuffer.dataLen,
                m_frameBuffer.data);

        if (rc) {
            reportError(rc);
        }
    } else {
        reportError(B42_ERROR_INVALID_COMMAND);
    }
}

void B42::sendFrame(uint8_t command, uint8_t dataLen, uint8_t* data)
{
    m_commStream->write(command | (dataLen << 4));
    for (uint8_t i=0; i < dataLen; ++i) {
        m_commStream->write(data[i] | ((i+1) << 6));
    }
}

void B42::reportError(B42ReturnCode rc)
{
    if (m_errorHandler) {
        m_errorHandler(rc);
    }
}

void B42::registerCommandHandler(uint8_t command, CommandHandlerPtr handler)
{
    m_cmdHandlers[command] = handler;
}

void B42::setErrorHandler(ErrorHandlerPtr handler)
{
    m_errorHandler = handler;
}

B42 b42;
