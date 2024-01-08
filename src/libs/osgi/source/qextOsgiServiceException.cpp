/*=============================================================================

  Library: CTK

  Copyright (c) German Cancer Research Center,
    Division of Medical and Biological Informatics

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=============================================================================*/

#include <qextOsgiServiceException.h>

#include <QDebug>

//----------------------------------------------------------------------------
QExtOsgiServiceException::QExtOsgiServiceException(const QString &msg, const Type& type)
    : QExtRuntimeException(msg),
    type(type)
{

}

//----------------------------------------------------------------------------
QExtOsgiServiceException::QExtOsgiServiceException(const QString &msg, const Type& type,
                                         const QExtException& cause)
    : QExtRuntimeException(msg, cause),
    type(type)
{

}

//----------------------------------------------------------------------------
QExtOsgiServiceException::QExtOsgiServiceException(const QString &msg, const QExtException& cause)
    : QExtRuntimeException(msg, cause),
    type(UNSPECIFIED)
{

}

//----------------------------------------------------------------------------
QExtOsgiServiceException::QExtOsgiServiceException(const QExtOsgiServiceException& o)
    : QExtRuntimeException(o), type(o.type)
{

}

//----------------------------------------------------------------------------
QExtOsgiServiceException& QExtOsgiServiceException::operator=(const QExtOsgiServiceException& o)
{
    QExtRuntimeException::operator=(o);
    type = o.type;
    return *this;
}

//----------------------------------------------------------------------------
QExtOsgiServiceException::~QExtOsgiServiceException() throw()
{

}

//----------------------------------------------------------------------------
const char *QExtOsgiServiceException::name() const throw()
{
    return "qextOsgiServiceException";
}

//----------------------------------------------------------------------------
QExtOsgiServiceException* QExtOsgiServiceException::clone() const
{
    return new QExtOsgiServiceException(*this);
}

//----------------------------------------------------------------------------
void QExtOsgiServiceException::rethrow() const
{
    throw *this;
}

//----------------------------------------------------------------------------
QExtOsgiServiceException::Type QExtOsgiServiceException::getType() const
{
    return type;
}

