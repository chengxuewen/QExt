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

#include "qtklogstream.h"
#include "qtklogservice.h"

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

QTKLogStream::QTKLogStream(QTKLogService *bLogService, int iLevel, const std::exception *pExc,
                           const char *pFile, const char *pFunction, int iLine)
    : m_bLogged(false),
      m_bLogService(bLogService),
      m_iLevel(iLevel),
      m_pExc(pExc),
      m_pFile(pFile),
      m_pFunction(pFunction),
      m_iLine(iLine)
{

}

QTKLogStream::QTKLogStream(const QTKLogStream &logStream)
    : m_strMsg(logStream.m_strMsg),
      m_bLogged(false),
      m_bLogService(logStream.m_bLogService),
      m_iLevel(logStream.m_iLevel),
      m_pExc(logStream.m_pExc),
      m_pFile(logStream.m_pFile),
      m_pFunction(logStream.m_pFunction),
      m_iLine(logStream.m_iLine)
{
    m_textStream.setString(&m_strMsg);
}

QTKLogStream::~QTKLogStream()
{
    if (!m_bLogged && m_bLogService) {
        m_bLogService->log(m_iLevel, m_strMsg, m_pExc, m_pFile, m_pFunction, m_iLine);
    }
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
