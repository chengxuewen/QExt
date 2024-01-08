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


#include <qextOsgiLogService.h>

const int QExtOsgiLogService::LOG_ERROR = 1;
const int QExtOsgiLogService::LOG_WARNING = 2;
const int QExtOsgiLogService::LOG_INFO = 3;
const int QExtOsgiLogService::LOG_DEBUG = 4;

//----------------------------------------------------------------------------
QExtOsgiLogStreamWithServiceRef::QExtOsgiLogStreamWithServiceRef(QExtOsgiLogService *logService, const QExtOsgiServiceReference &sr,
                                                                 int level, const std::exception* exc, const char *file,
                                                                 const char *function, int line)
    : QExtOsgiLogStream(logService, level, exc, file, function, line), sr(sr)
{

}

//----------------------------------------------------------------------------
QExtOsgiLogStreamWithServiceRef::QExtOsgiLogStreamWithServiceRef(const QExtOsgiLogStreamWithServiceRef &logStreamWithRef)
    : QExtOsgiLogStream(logStreamWithRef), sr(logStreamWithRef.sr)
{

}

//----------------------------------------------------------------------------
QExtOsgiLogStreamWithServiceRef::~QExtOsgiLogStreamWithServiceRef()
{
    if (!logged)
    {
        logService->log(sr, level, msg, exc, file, function, line);
        logged = true;
    }
}

//----------------------------------------------------------------------------
QExtOsgiNullLogStream::QExtOsgiNullLogStream() : QExtOsgiLogStream(0, 0) {}

//----------------------------------------------------------------------------
QExtOsgiNullLogStream::~QExtOsgiNullLogStream()
{
    logged = true;
}
