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


#include <qextException.h>

#include <QDebug>

#include <typeinfo>

// --------------------------------------------------------------------------
QExtException::TraceManipulator::TraceManipulator(const QExtException* e)
    : Exc(e)
{
}

// --------------------------------------------------------------------------
QDebug QExtException::TraceManipulator::print(QDebug dbg) const
{
    if (Exc)
    {
        Exc->printStackTrace(dbg);
    }
    return dbg.maybeSpace();
}

// --------------------------------------------------------------------------
QExtException::QExtException(const QString& msg)
    : Msg(msg), NestedException(0)
{
}

// --------------------------------------------------------------------------
QExtException::QExtException(const QString& msg, const QExtException& cause)
    : Msg(msg), NestedException(cause.clone())
{
}

// --------------------------------------------------------------------------
QExtException::QExtException(const QExtException& exc)
    : std::exception(exc), QExtBackTrace(exc), Msg(exc.Msg)
{
    NestedException = exc.NestedException ? exc.NestedException->clone() : 0;
}

// --------------------------------------------------------------------------
QExtException::~QExtException() throw()
{
    delete NestedException;
}

// --------------------------------------------------------------------------
QExtException& QExtException::operator=(const QExtException& exc)
{
    if (&exc != this)
    {
        delete NestedException;
        Msg = exc.Msg;
        NestedException = exc.NestedException ? exc.NestedException->clone() : 0;
    }
    return *this;
}

// --------------------------------------------------------------------------
const QExtException* QExtException::cause() const throw()
{
    return NestedException;
}

// --------------------------------------------------------------------------
void QExtException::setCause(const QExtException& cause)
{
    delete NestedException;
    NestedException = cause.clone();
}

// --------------------------------------------------------------------------
const char *QExtException::name() const throw()
{
    return "QExtException";
}

// --------------------------------------------------------------------------
const char* QExtException::className() const throw()
{
    return typeid(*this).name();
}

// --------------------------------------------------------------------------
const char* QExtException::what() const throw()
{
    if (WhatMsg.empty())
    {
        WhatMsg = std::string(name());
        if (!Msg.isEmpty())
        {
            WhatMsg += ": ";
            WhatMsg += Msg.toStdString();
        }
    }
    return WhatMsg.c_str();
}

// --------------------------------------------------------------------------
QString QExtException::message() const throw()
{
    return Msg;
}

// --------------------------------------------------------------------------
QExtException::TraceManipulator QExtException::printStackTrace() const
{
    return TraceManipulator(this);
}

// --------------------------------------------------------------------------
QExtException* QExtException::clone() const
{
    return new QExtException(*this);
}

// --------------------------------------------------------------------------
void QExtException::rethrow() const
{
    throw *this;
}

// --------------------------------------------------------------------------
QDebug QExtException::printStackTrace(QDebug dbg) const
{
    QSet<const QExtException*> dejaVu;
    dejaVu.insert(this);

    // Print our stack trace
    dbg.nospace() << this->what() << '\n';
    QList<QString> trace = stackTrace();
    foreach(QString traceElement, trace)
    {
        dbg.nospace() << "\tat " << qPrintable(traceElement) << '\n';
    }

    // Print cause, if any
    if (NestedException)
    {
        NestedException->printEnclosedStackTrace(dbg, trace, "Caused by: ", "", dejaVu);
    }
    return dbg;
}

// --------------------------------------------------------------------------
void QExtException::printEnclosedStackTrace(QDebug dbg, const QList<QString>& enclosingTrace,
                                            const QString& caption, const QString& prefix,
                                            QSet<const QExtException*>& dejaVu)
{
    if (dejaVu.contains(this))
    {
        dbg.nospace() << "\t[CIRCULAR REFERENCE:" << this->what() << "]\n";
    }
    else
    {
        dejaVu.insert(this);
        // Compute number of frames in common between this and enclosing trace
        QList<QString> trace = stackTrace();
        int m = trace.size() - 1;
        int n = enclosingTrace.size() - 1;
        while (m >= 0 && n >=0 && trace[m] == enclosingTrace[n])
        {
            m--; n--;
        }
        int framesInCommon = trace.size() - 1 - m;

        // Print our stack trace
        dbg.nospace() << qPrintable(prefix) << qPrintable(caption) << this->what() << '\n';
        for (int i = 0; i <= m; i++)
        {
            dbg.nospace() << qPrintable(prefix) << "\tat " << qPrintable(trace[i]) << '\n';
        }
        if (framesInCommon != 0)
        {
            dbg.nospace() << qPrintable(prefix) << "\t... " << framesInCommon << " more\n";
        }

        // Print cause, if any
        if (NestedException)
        {
            NestedException->printEnclosedStackTrace(dbg, trace, "Caused by: ", prefix, dejaVu);
        }
    }
}

//----------------------------------------------------------------------------
QDebug operator<<(QDebug dbg, const QExtException& exc)
{
    dbg << exc.what();
    return dbg.maybeSpace();
}

//----------------------------------------------------------------------------
QDebug operator<<(QDebug dbg, const QExtException::TraceManipulator& trace)
{
    return trace.print(dbg);
}

QEXT_IMPLEMENT_EXCEPTION(QExtUnsupportedOperationException, QExtException, "QExtUnsupportedOperationException")
QEXT_IMPLEMENT_EXCEPTION(QExtRuntimeException, QExtException, "QExtRuntimeException")
QEXT_IMPLEMENT_EXCEPTION(QExtInvalidArgumentException, QExtRuntimeException, "QExtInvalidArgumentException")
QEXT_IMPLEMENT_EXCEPTION(QExtIllegalStateException, QExtRuntimeException, "QExtIllegalStateException")
