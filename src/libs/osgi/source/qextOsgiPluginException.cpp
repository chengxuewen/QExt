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

#include <qextOsgiPluginException.h>

#include <QDebug>

//----------------------------------------------------------------------------
QExtOsgiPluginException::QExtOsgiPluginException(const QString& msg, const Type& type)
  : QExtRuntimeException(msg),
    type(type)
{

}

//----------------------------------------------------------------------------
QExtOsgiPluginException::QExtOsgiPluginException(const QString& msg, const Type& type, const QExtException& cause)
  : QExtRuntimeException(msg, cause),
    type(type)
{

}

//----------------------------------------------------------------------------
QExtOsgiPluginException::QExtOsgiPluginException(const QString& msg, const QExtException& cause)
  : QExtRuntimeException(msg, cause),
    type(UNSPECIFIED)
{

}

//----------------------------------------------------------------------------
QExtOsgiPluginException::QExtOsgiPluginException(const QExtOsgiPluginException& o)
  : QExtRuntimeException(o), type(o.type)
{

}

//----------------------------------------------------------------------------
QExtOsgiPluginException& QExtOsgiPluginException::operator=(const QExtOsgiPluginException& o)
{
  QExtRuntimeException::operator=(o);
  type = o.type;
  return *this;
}

//----------------------------------------------------------------------------
QExtOsgiPluginException::~QExtOsgiPluginException() throw()
{
}

//----------------------------------------------------------------------------
const char* QExtOsgiPluginException::name() const throw()
{
  return "qextOsgiPluginException";
}

//----------------------------------------------------------------------------
QExtOsgiPluginException* QExtOsgiPluginException::clone() const
{
  return new QExtOsgiPluginException(*this);
}

//----------------------------------------------------------------------------
void QExtOsgiPluginException::rethrow() const
{
  throw *this;
}

//----------------------------------------------------------------------------
QExtOsgiPluginException::Type QExtOsgiPluginException::getType() const
{
  return type;
}
