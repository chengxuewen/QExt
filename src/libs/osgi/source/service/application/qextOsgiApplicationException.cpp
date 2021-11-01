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

#include "qtkapplicationexception.h"

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

const int QTKApplicationException::APPLICATION_LOCKED	= 0x01;
const int QTKApplicationException::APPLICATION_NOT_LAUNCHABLE = 0x02;
const int QTKApplicationException::APPLICATION_INTERNAL_ERROR = 0x03;
const int QTKApplicationException::APPLICATION_SCHEDULING_FAILED = 0x04;
const int QTKApplicationException::APPLICATION_DUPLICATE_SCHEDULE_ID = 0x05;
const int QTKApplicationException::APPLICATION_EXITVALUE_NOT_AVAILABLE = 0x06;
const int QTKApplicationException::APPLICATION_INVALID_STARTUP_ARGUMENT = 0x07;

QTKApplicationException::QTKApplicationException(int iErrorCode)
  : QTKException("")
  , m_iErrorCode(iErrorCode)
{
}

QTKApplicationException::QTKApplicationException(int iErrorCode, const QTKException& cause)
  : QTKException("", cause)
  , m_iErrorCode(iErrorCode)
{
}

QTKApplicationException::QTKApplicationException(int iErrorCode, const QString& strMessage)
  : QTKException(strMessage)
  , m_iErrorCode(iErrorCode)
{
}

QTKApplicationException::QTKApplicationException(int iErrorCode, const QString& strMessage, const QTKException& cause)
  : QTKException(strMessage, cause)
  , m_iErrorCode(iErrorCode)
{
}

QTKApplicationException::~QTKApplicationException() throw()
{

}

const char* QTKApplicationException::name() const throw()
{
  return "Application Exception";
}

QTKApplicationException* QTKApplicationException::clone() const
{
  return new QTKApplicationException(*this);
}

void QTKApplicationException::rethrow() const
{
  throw *this;
}

int QTKApplicationException::GetErrorCode() const
{
  return m_iErrorCode;
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
