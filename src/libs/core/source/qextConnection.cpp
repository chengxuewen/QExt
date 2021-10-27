/*************************************************************************************
**
** Library: CommonFramework
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



QEXTConnection::QEXTConnection()
    : m_slot(QEXT_DECL_NULLPTR)
{
}

QEXTConnection::QEXTConnection(const QEXTConnection &other)
    : m_slot(other.m_slot)
{
}

QEXTConnection::QEXTConnection(SlotFunctionBase &slot)
    : m_slot(&slot)
{
}

QEXTConnection::~QEXTConnection()
{

}

QEXTConnection &QEXTConnection::operator=(const QEXTConnection &other)
{
    this->setSlot(other.m_slot);
    return *this;
}

bool QEXTConnection::isEmpty() const
{
    return (!m_slot || m_slot->isValid());
}

bool QEXTConnection::isBlocked() const
{
    return (m_slot ? m_slot->isBlocked() : false);
}

bool QEXTConnection::setBlock(bool block)
{
    return (m_slot ? m_slot->setBlock(block) : false);
}

bool QEXTConnection::unblock()
{
    return (m_slot ? m_slot->unblock() : false);
}

bool QEXTConnection::isConnected() const
{
    return !this->isEmpty();
}

void QEXTConnection::disconnect()
{
    if (m_slot)
    {
        m_slot->disconnect(); // This notifies slot_'s parent.
    }
}

void *QEXTConnection::notify(void *data)
{
    QEXTConnection *self = reinterpret_cast<QEXTConnection *>(data);
    self->m_slot = QEXT_DECL_NULLPTR;
    return QEXT_DECL_NULLPTR;
}

void QEXTConnection::setSlot(SlotFunctionBase *slot)
{
    m_slot = slot;
}

QEXTConnection::operator bool()
{
    return !this->isEmpty();
}


