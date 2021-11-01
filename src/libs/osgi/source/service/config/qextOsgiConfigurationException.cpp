/****************************************************************************
** Library: QTK
**
** Copyright (c) German Cancer Research Center,
**     Division of Medical and Biological Informatics
** Copyright (c) chengxuewen <1398831004@qq.com>
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
** http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
**
****************************************************************************/

#include "qtkconfigurationexception.h"

#include <QDebug>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

QTKConfigurationException::QTKConfigurationException(const QString& strProperty, const QString& strReason)
  : QTKRuntimeException(strProperty + " : " + strReason),
    property(strProperty), reason(strReason)
{

}

QTKConfigurationException::QTKConfigurationException(const QString& strProperty, const QString& strReason,
                                                     const QTKException& cause)
  : QTKRuntimeException(strProperty + " : " + strReason, cause),
    property(strProperty), reason(strReason)
{

}

QTKConfigurationException::QTKConfigurationException(const QTKConfigurationException& o)
  : QTKRuntimeException(o), property(o.property), reason(o.reason)
{

}

QTKConfigurationException& QTKConfigurationException::operator=(const QTKConfigurationException& o)
{
  QTKRuntimeException::operator =(o);
  property = o.property;
  reason = o.reason;
  return *this;
}

QTKConfigurationException::~QTKConfigurationException() throw()
{
}

const char* QTKConfigurationException::name() const throw()
{
  return "QTKConfigurationException";
}

QTKConfigurationException* QTKConfigurationException::clone() const
{
  return new QTKConfigurationException(*this);
}

void QTKConfigurationException::rethrow() const
{
  throw *this;
}

QString QTKConfigurationException::getProperty() const
{
  return property;
}

QString QTKConfigurationException::getReason() const
{
  return reason;
}

QDebug operator<<(QDebug dbg, const QTKConfigurationException& exc)
{
  dbg << "QTKConfigurationException:" << exc.what();
  return dbg.maybeSpace();
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
