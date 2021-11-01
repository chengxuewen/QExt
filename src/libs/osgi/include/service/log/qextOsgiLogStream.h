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

#ifndef QTKLOGSTREAM_H
#define QTKLOGSTREAM_H

#include "../../qtkpluginframework_global.h"

#include <QTextStream>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKLogService;

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKLogStream class
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKLogStream
{
public:
    QTKLogStream(QTKLogService *bLogService, int iLevel, const std::exception *pExc = nullptr,
                 const char *pFile = nullptr, const char *pFunction = nullptr, int iLine = -1);
    QTKLogStream(const QTKLogStream &logStream);

    virtual ~QTKLogStream();

    template<class T>
    QTKLogStream& operator <<(const T& t) {
        m_textStream << t;
        return *this;
    }

    QTKLogStream& operator <<(const char* c) {
        m_textStream << c;
        return *this;
    }

    QTKLogStream& operator <<(bool b) {
        m_textStream << (b ? "true" : "false");
        return *this;
    }

protected:
    QString m_strMsg;
    QTextStream m_textStream;
    bool m_bLogged;

    QTKLogService *m_bLogService;
    int m_iLevel;
    const std::exception *m_pExc;

    const char *m_pFile;
    const char *m_pFunction;
    const int m_iLine;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKLOGSTREAM_H
