/*************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
** Copyright 2002, The libsigc++ Development Team
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files (the "Software"),
** to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense,
** and/or sell copies of the Software, and to permit persons to whom the
** Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
*************************************************************************************/

#include <qextConnection.h>



QExtConnection::QExtConnection()
    : m_slot(QEXT_NULLPTR)
{
}

QExtConnection::QExtConnection(const QExtConnection &other)
    : m_slot(other.m_slot)
{
}

QExtConnection::QExtConnection(SlotFunctionBase &slot)
    : m_slot(&slot)
{
}

QExtConnection::~QExtConnection()
{

}

QExtConnection &QExtConnection::operator=(const QExtConnection &other)
{
    this->setSlot(other.m_slot);
    return *this;
}

bool QExtConnection::isEmpty() const
{
    return (!m_slot || m_slot->isValid());
}

bool QExtConnection::isBlocked() const
{
    return (m_slot ? m_slot->isBlocked() : false);
}

bool QExtConnection::setBlock(bool block)
{
    return (m_slot ? m_slot->setBlock(block) : false);
}

bool QExtConnection::unblock()
{
    return (m_slot ? m_slot->unblock() : false);
}

bool QExtConnection::isConnected() const
{
    return !this->isEmpty();
}

void QExtConnection::disconnect()
{
    if (m_slot)
    {
        m_slot->disconnect(); // This notifies slot_'s parent.
    }
}

void *QExtConnection::notify(void *data)
{
    QExtConnection *self = reinterpret_cast<QExtConnection *>(data);
    self->m_slot = QEXT_NULLPTR;
    return QEXT_NULLPTR;
}

void QExtConnection::setSlot(SlotFunctionBase *slot)
{
    m_slot = slot;
}

QExtConnection::operator bool()
{
    return !this->isEmpty();
}


