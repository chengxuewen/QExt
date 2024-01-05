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

#include <qext/osgi/service/application/qextOsgiApplicationException.h>

const int QExtOsgiApplicationException::APPLICATION_LOCKED	= 0x01;
const int QExtOsgiApplicationException::APPLICATION_NOT_LAUNCHABLE = 0x02;
const int QExtOsgiApplicationException::APPLICATION_INTERNAL_ERROR = 0x03;
const int QExtOsgiApplicationException::APPLICATION_SCHEDULING_FAILED = 0x04;
const int QExtOsgiApplicationException::APPLICATION_DUPLICATE_SCHEDULE_ID = 0x05;
const int QExtOsgiApplicationException::APPLICATION_EXITVALUE_NOT_AVAILABLE = 0x06;
const int QExtOsgiApplicationException::APPLICATION_INVALID_STARTUP_ARGUMENT = 0x07;


//----------------------------------------------------------------------------
QExtOsgiApplicationException::QExtOsgiApplicationException(int errorCode)
    : QExtException("")
    , errorCode(errorCode)
{
}

//----------------------------------------------------------------------------
QExtOsgiApplicationException::QExtOsgiApplicationException(int errorCode, const QExtException& cause)
    : QExtException("", cause)
    , errorCode(errorCode)
{
}

//----------------------------------------------------------------------------
QExtOsgiApplicationException::QExtOsgiApplicationException(int errorCode, const QString& message)
    : QExtException(message)
    , errorCode(errorCode)
{
}

//----------------------------------------------------------------------------
QExtOsgiApplicationException::QExtOsgiApplicationException(int errorCode, const QString& message, const QExtException& cause)
    : QExtException(message, cause)
    , errorCode(errorCode)
{
}

//----------------------------------------------------------------------------
QExtOsgiApplicationException::~QExtOsgiApplicationException() throw()
{

}

//----------------------------------------------------------------------------
const char* QExtOsgiApplicationException::name() const throw()
{
    return "Application Exception";
}

//----------------------------------------------------------------------------
QExtOsgiApplicationException* QExtOsgiApplicationException::clone() const
{
    return new QExtOsgiApplicationException(*this);
}

//----------------------------------------------------------------------------
void QExtOsgiApplicationException::rethrow() const
{
    throw *this;
}

//----------------------------------------------------------------------------
int QExtOsgiApplicationException::GetErrorCode() const
{
    return errorCode;
}
