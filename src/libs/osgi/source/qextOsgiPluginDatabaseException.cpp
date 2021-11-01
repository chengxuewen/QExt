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

#include "qtkplugindatabaseexception.h"

#include <QDebug>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

QTKPluginDatabaseException::QTKPluginDatabaseException(const QString &strMsg, const Type &eType)
    : QTKRuntimeException(strMsg),
      m_eType(eType)
{

}

QTKPluginDatabaseException::QTKPluginDatabaseException(const QString &strMsg, const Type &eType,
                                                       const QTKException &cause)
    : QTKRuntimeException(strMsg, cause),
      m_eType(eType)
{

}

QTKPluginDatabaseException::QTKPluginDatabaseException(const QString &strMsg,
                                                       const QTKException &cause)
    : QTKRuntimeException(strMsg, cause),
      m_eType(Type_Unspecified)
{

}

QTKPluginDatabaseException::QTKPluginDatabaseException(const QTKPluginDatabaseException &other)
    : QTKRuntimeException(other),
      m_eType(other.m_eType)
{

}

QTKPluginDatabaseException& QTKPluginDatabaseException::operator=(const QTKPluginDatabaseException &other)
{
    QTKRuntimeException::operator=(other);
    m_eType = other.m_eType;
    return *this;
}

QTKPluginDatabaseException::~QTKPluginDatabaseException() throw()
{

}

const char* QTKPluginDatabaseException::name() const throw()
{
    return "QTKPluginDatabaseException";
}

QTKPluginDatabaseException* QTKPluginDatabaseException::clone() const
{
    return new QTKPluginDatabaseException(*this);
}

void QTKPluginDatabaseException::rethrow() const
{
    throw *this;
}

QTKPluginDatabaseException::Type QTKPluginDatabaseException::getType() const
{
    return m_eType;
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
