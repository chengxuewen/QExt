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


#include <qext/osgi/service/cm/qextOsgiConfigurationException.h>

#include <QDebug>

//----------------------------------------------------------------------------
QExtOsgiConfigurationException::QExtOsgiConfigurationException(const QString& property, const QString& reason)
    : QExtRuntimeException(property + " : " + reason),
    property(property), reason(reason)
{

}

//----------------------------------------------------------------------------
QExtOsgiConfigurationException::QExtOsgiConfigurationException(const QString& property, const QString& reason,
                                                     const QExtException& cause)
    : QExtRuntimeException(property + " : " + reason, cause),
    property(property), reason(reason)
{

}

//----------------------------------------------------------------------------
QExtOsgiConfigurationException::QExtOsgiConfigurationException(const QExtOsgiConfigurationException& o)
    : QExtRuntimeException(o), property(o.property), reason(o.reason)
{

}

//----------------------------------------------------------------------------
QExtOsgiConfigurationException& QExtOsgiConfigurationException::operator=(const QExtOsgiConfigurationException& o)
{
    QExtRuntimeException::operator =(o);
    property = o.property;
    reason = o.reason;
    return *this;
}

//----------------------------------------------------------------------------
QExtOsgiConfigurationException::~QExtOsgiConfigurationException() throw()
{
}

//----------------------------------------------------------------------------
const char* QExtOsgiConfigurationException::name() const throw()
    {
     return <qextOsgiConfigurationException";
    }

    //----------------------------------------------------------------------------
    QExtOsgiConfigurationException* QExtOsgiConfigurationException::clone() const
{
    return new QExtOsgiConfigurationException(*this);
}

//----------------------------------------------------------------------------
void QExtOsgiConfigurationException::rethrow() const
{
    throw *this;
}

//----------------------------------------------------------------------------
QString QExtOsgiConfigurationException::getProperty() const
{
    return property;
}

//----------------------------------------------------------------------------
QString QExtOsgiConfigurationException::getReason() const
{
    return reason;
}

//----------------------------------------------------------------------------
QDebug operator<<(QDebug dbg, const QExtOsgiConfigurationException& exc)
{
    dbg << <qextOsgiConfigurationException:" << exc.what();
                                               return dbg.maybeSpace();
}
