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


#ifndef _QEXTEXCEPTION_H
#define _QEXTEXCEPTION_H

#include <qextGlobal.h>
#include <qextBackTrace.h>

#include <QSet>
#include <QString>

/**
 * @ingroup Core
 * @brief The base class for all exceptions defined in QExt.
 *
 * This exception class takes a QString object as the message text and can optionally store another QExtException
 * instance which caused this exception.
 *
 * QExtException classes can be copied, saved, and rethrown.
 */
class QEXT_CORE_API QExtException : public std::exception, public QExtBackTrace
{
public:
    class TraceManipulator
    {
    public:
        TraceManipulator(const QExtException* e);

        QDebug print(QDebug dbg) const;

    private:
        const QExtException* Exc;
    };

    /**
     * @brief Create a new QExtException.
     * @param msg The exception message.
     */
    explicit QExtException(const QString &msg);

    /**
     * @brief Create a new QExtException containing another exception as the cause.
     * @param msg The exception message.
     * @param cause The nested exception causing this exception.
     */
    QExtException(const QString &msg, const QExtException& cause);

    /**
     * @brief Copy constructor.
     * @param o The exception to copy.
     */
    QExtException(const QExtException& o);

    /**
   * @brief Assignment operator.
   * @param o The exception to assign to this exception.
   * @return
   */
    QExtException& operator=(const QExtException& o);

    ~QExtException() throw();

    /**
   * @brief Gets the nested exception which caused this exception.
   * @return The nested exception, or <code>NULL</code> if there is none.
   */
    const QExtException* cause() const throw();

    /**
   * @brief Sets the cause for this exception.
   * @param cause The exception causing this exception.
   */
    void setCause(const QExtException& cause);

    /**
   * @brief Returns the name for this exception.
   * @return The exception name.
   */
    virtual const char *name() const throw();

    /**
   * @brief Returns the class name for this exception.
   * @return The exception class name.
   */
    virtual const char *className() const throw();

    /**
   * @brief Returns a static string describing this exception.
   * @return The exception description.
   */
    virtual const char *what() const throw();

    /**
   * @brief Returns the detail message string of this exception.
   * @return The detail exception message.
   */
    QString message() const throw();

    /**
   * @brief Returns an object suitable for printing this executable
   * and its backtrace via qDebug().
   *
   * Example usage:
   * \code
   * QExtException exc("My error");
   * qDebug() << exc.printStackTrace();
   * \endcode
   *
   * @return A helper object for streaming to qDebug().
   */
    TraceManipulator printStackTrace() const;

    /**
   * @brief Creates a copy of this exception. Use rethrow() to throw the
   * copy again.
   * @return A copy of this exception.
   */
    virtual QExtException* clone() const;

    /**
   * @brief (Re)Throws this exception.
   */
    virtual void rethrow() const;

protected:

    friend class TraceManipulator;

    /**
   * @brief Print the stack trace of this exception using the given QDebug object.
   * @param dbg
   * @return
   */
    virtual QDebug printStackTrace(QDebug dbg) const;

private:

    QString Msg;
    mutable std::string WhatMsg;
    QExtException* NestedException;

    void printEnclosedStackTrace(QDebug dbg, const QList<QString>& enclosingTrace,
                                 const QString &caption, const QString &prefix,
                                 QSet<const QExtException*>& dejaVu);

};

//---------------------------------------------------------------------------
/**
 * \ingroup Core
 */
QEXT_CORE_API QDebug operator<<(QDebug dbg, const QExtException& exc);

//---------------------------------------------------------------------------
/**
 * \ingroup Core
 */
QEXT_CORE_API QDebug operator<<(QDebug dbg, const QExtException::TraceManipulator& trace);

//---------------------------------------------------------------------------
/**
 * \ingroup Core
 *
 * \brief Quickly declare a QExtException sub-class.
 * \param API The export macro.
 * \param CLS The class name for the QExtException sub-class.
 * \param BASE The class name of the actual super class.
 */
#define QEXT_DECLARE_EXCEPTION(API, CLS, BASE) \
class API CLS : public BASE \
{ \
        public: \
        explicit CLS(const QString &msg); \
        CLS(const QString &msg, const QExtException& exc); \
        CLS(const CLS& exc); \
        ~CLS() throw(); \
        CLS& operator = (const CLS& exc); \
        const char *name() const throw(); \
        CLS* clone() const; \
        void rethrow() const ; \
};

//---------------------------------------------------------------------------
/**
 * \ingroup Core
 *
 * \brief Quickly implement a QExtException sub-class
 * \param CLS The class name for the QExtException sub-class.
 * \param BASE The class name of the actual super class.
 * \param NAME A human-readable name for this exception class.
 */
#define QEXT_IMPLEMENT_EXCEPTION(CLS, BASE, NAME) \
CLS::CLS(const QString &msg) : BASE(msg) { } \
    CLS::CLS(const QString &msg, const QExtException& exc) : BASE(msg, exc) { } \
    CLS::CLS(const CLS& exc) : BASE(exc) { } \
    CLS::~CLS() throw() { } \
    CLS& CLS::operator = (const CLS& exc) { BASE::operator = (exc); return *this; } \
    const char *CLS::name() const throw() { return NAME; } \
    CLS* CLS::clone() const { return new CLS(*this); } \
    void CLS::rethrow() const { throw *this; }

QEXT_DECLARE_EXCEPTION(QEXT_CORE_API, QExtRuntimeException, QExtException)
QEXT_DECLARE_EXCEPTION(QEXT_CORE_API, QExtIllegalStateException, QExtRuntimeException)
QEXT_DECLARE_EXCEPTION(QEXT_CORE_API, QExtUnsupportedOperationException, QExtException)
QEXT_DECLARE_EXCEPTION(QEXT_CORE_API, QExtInvalidArgumentException, QExtRuntimeException)

#endif // _QEXTEXCEPTION_H
