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

#include "qtkserviceexception.h"

#include <QDebug>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

QTKServiceException::QTKServiceException(const QString &strMsg, const QTKServiceException::Type &eType)
    : QTKRuntimeException(strMsg),
      m_eType(eType)
{

}

QTKServiceException::QTKServiceException(const QString &strMsg, const QTKServiceException::Type &eType,
                                         const QTKException &cause)
    : QTKRuntimeException(strMsg, cause),
      m_eType(eType)
{

}

QTKServiceException::QTKServiceException(const QString &strMsg, const QTKException &cause)
    : QTKRuntimeException(strMsg, cause),
      m_eType(Type_Unspecified)
{

}

QTKServiceException::QTKServiceException(const QTKServiceException &other)
    : QTKRuntimeException(other),
      m_eType(other.m_eType)
{

}

QTKServiceException::~QTKServiceException() throw()
{

}

const char *QTKServiceException::name() const throw()
{
    return "QTKServiceException";
}

QTKServiceException *QTKServiceException::clone() const
{
    return new QTKServiceException(*this);
}

void QTKServiceException::rethrow() const
{
    throw *this;
}

QTKServiceException::Type QTKServiceException::getType() const
{
    return m_eType;
}

QTKServiceException &QTKServiceException::operator=(const QTKServiceException &other)
{
    QTKRuntimeException::operator=(other);
    m_eType = other.m_eType;
    return *this;
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
