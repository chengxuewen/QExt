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

#include "qtklogservice.h"

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

const int QTKLogService::LOG_ERROR = 1;
const int QTKLogService::LOG_WARNING = 2;
const int QTKLogService::LOG_INFO = 3;
const int QTKLogService::LOG_DEBUG = 4;

QTKLogStreamWithServiceRef::QTKLogStreamWithServiceRef(QTKLogService *bLogService, const QTKServiceReference &serviceRef,
                                                       int iLevel, const std::exception *pExc, const char *pFile,
                                                       const char *pFunction, int iLine)
    : QTKLogStream(bLogService, iLevel, pExc, pFile, pFunction, iLine), m_serviceRef(serviceRef)
{

}

QTKLogStreamWithServiceRef::QTKLogStreamWithServiceRef(const QTKLogStreamWithServiceRef &logStreamWithRef)
    : QTKLogStream(logStreamWithRef), m_serviceRef(logStreamWithRef.m_serviceRef)
{

}

QTKLogStreamWithServiceRef::~QTKLogStreamWithServiceRef()
{
    if (!m_bLogged) {
        m_bLogService->log(m_serviceRef, m_iLevel, m_strMsg, m_pExc, m_pFile, m_pFunction, m_iLine);
        m_bLogged = true;
    }
}

QTKNullLogStream::QTKNullLogStream() : QTKLogStream(0, 0)
{

}

QTKNullLogStream::~QTKNullLogStream()
{
    m_bLogged = true;
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
