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


#ifndef _QEXTOSGILOGSTREAM_H
#define _QEXTOSGILOGSTREAM_H

#include <qextOsgiGlobal.h>

#include <QTextStream>

struct QExtOsgiLogService;

/**
 * \ingroup LogService
 */
class QEXT_OSGI_API QExtOsgiLogStream
{
public:

    QExtOsgiLogStream(QExtOsgiLogService* logService, int level, const std::exception* exc = 0,
                 const char* file = 0, const char* function = 0, int line = -1);
    QExtOsgiLogStream(const QExtOsgiLogStream& logStream);

    virtual ~QExtOsgiLogStream();

    template<class T>
    QExtOsgiLogStream& operator <<(const T& t)
    {
        ts << t;
        return *this;
    }

    QExtOsgiLogStream& operator <<(const char* c)
    {
        ts << c;
        return *this;
    }

    QExtOsgiLogStream& operator <<(bool b)
    {
        ts << (b ? "true" : "false");
        return *this;
    }

protected:

    QString msg;
    QTextStream ts;
    bool logged;

    QExtOsgiLogService* logService;
    int level;
    const std::exception* exc;

    const char* file;
    const char* function;
    const int line;
};

#endif // _QEXTOSGILOGSTREAM_H
