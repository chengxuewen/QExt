/******************************************************************************
 *
 * This file is part of Log4Qt library.
 *
 * Copyright (C) 2007 - 2020 Log4Qt contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/

#ifndef _QEXTLOGERROR_H
#define _QEXTLOGERROR_H

#include <qextLoggingGlobal.h>

#include <QVariant>
#include <QString>

/*!
 * Creates an QExtLogError object with the error message \a message, the error
 * code \a code and the context \a context. The symbol of the error is
 * set to \a code as string value.
 *
 * The following example logs an error, if a character is not a digit.
 *
 * \code
 * if (!c.isDigit())
     * {
     *     Error e = QEXT_LOG_ERROR(QT_TR_NOOP("Found character '%1' where digit was expected."),
     *                            Error_LayoutExpectedDigitFailed,
     *                            "Log4Qt::PatternFormatter");
     *     e << QString(c);
 *     logger()->error(e);
     * }
 * \endcode
 */
#define QEXT_LOG_ERROR(message, code, context) \
        QExtLogError(message, code, #code, context)

/*!
 * Creates an QExtLogError object with the error message \a message and the
 * error code \a code. The symbol of the error is set to \a code as string
 * value. The context is set to the class name of the current object. The
 * current objects class must be derived from QObject.
 *
 * The following example handles an error while opening a file.
 *
 * \code
 * if (!mpFile->open(mode))
 * {
 *      QExtLogError e = QEXT_LOG_QCLASS_ERROR(QT_TR_NOOP("Unable to open file '%1' for appender '%2'"),
     *                                       Error_AppenderOpenFileFailed);
 *      e << mFileName << name();
 *      e.addCausingError(QExtLogError(mpFile->errorString(), mpFile->error()));
 *      logger()->error(e);
 *      return;
 * }
 * \endcode
 */
#define QEXT_LOG_QCLASS_ERROR(message, code) \
        QExtLogError(message, code, #code, this->metaObject()->className())


/*!
 * This macro expands a numeric value of the form 0xMMmmPP (MM = major,
 * mm = minor, PP = patch) that specifies Log4Qt's version number.
 * This is the version against which the application is compiled.
 *
 * \sa \ref Log4Qt::QEXT_LOGGING_VERSION_STRING "QEXT_LOGGING_VERSION_STRING",
 *     \ref Log4Qt::LogManager::version() "LogManager::version()"
 */

/*!
 * The macro expands to a string that specifies the Log4Qt's version
 * number. This is the version against which the application is compiled.
 *
 * \sa \ref Log4Qt::QEXT_LOGGING_VERSION "QEXT_LOGGING_VERSION",
 *     \ref Log4Qt::LogManager::version() "LogManager::version()"
 */


/*!
 * \brief The class QExtLogError represents an error.
 *
 * The class error allows storing error information in a structured way.
 * The error message is stored separately from the information that may be
 * substituted into the message string. This way it is possible to access
 * all information after the error has been raised. It also allows to
 * translate the error at a later point in time or to get a translated and
 * a not translated error text (e.g. translated for the UI and not
 * translated for a log).
 *
 * The message is accessed using message() and setMessage(). Arguments for
 * the message can be added using addArg() or operator<<(). The arguments
 * can be retrieved using args(). The message with substituted arguments
 * is returned by messageWithArgs().
 *
 * An error code can be set as integer value code() and/or a symbolic value
 * symbol().
 *
 * To allow the translation of the message the error stores the translation
 * context (context(), setContext()). The translated message can be accessed
 * using translatedMessage() or using translatedMessageWithArgs(), if it
 * should contain the arguments.
 *
 * An error can have one or more related errors that caused it. An error is
 * related using addCausingError(). All causing errors can be retrieved using
 * causingErrors().
 *
 * A per thread error can be maintained using lastError() and setLastError().
 *
 * There are two macros avaiable to simplify the error creation. The macro
 * \ref Log4Qt::QEXT_LOG_ERROR "QEXT_LOG_ERROR" is used with classes not derived
 * from QObject. The macro \ref Log4Qt::QEXT_LOG_QCLASS_ERROR "QEXT_LOG_QCLASS_ERROR"
 * is used with classes derived from QObject.
 */
class QEXT_LOGGING_API QExtLogError
{
public:

    /*!
     * The enum Encoding defines the 8-bit encoding of a character string
     * arguments to \ref QExtLogError::QExtLogError(const char *, int, const char *,
     * const char *, Encoding) "QExtLogError::QExtLogError()".
     *
     * \sa \ref QExtLogError::QExtLogError(const char *, int, const char *, const char *, Encoding) "QExtLogError::QExtLogError()"
     */
    enum EncodingEnum
    {
        /*! LATIN-1 */
        Encoding_Latin1,
        /*!
         * The encoding specified by QTextCodec::codecForTr()
         * (Latin-1 if none has been set).
         */
        Encoding_CodecForTr,
        /*! UTF-8 */
        Encoding_UnicodeUtf8
    };

    enum ErrorCode
    {
        OK = 0,
        // AppenderSkeleton, FileAppender, WriterAppender
        Error_AppenderActivateMissingLayout,
        Error_AppenderActivateMissingWriter,
        Error_AppenderActivateMissingFile,
        Error_AppenderClosedFailed,
        Error_AppenderInvalidPattern,
        Error_AppenderNoOpenFile,
        Error_AppenderNotActivated,
        Error_AppenderOpenFileFailed,
        Error_AppenderWriteFileFailed,
        Error_AppenderRenameFileFailed,
        Error_AppenderRemoveFileFailed,
        Error_AppenderUseInvalidPattern,
        Error_AppenderUseMissingLayout,
        Error_AppenderUseMissingWriter,
        Error_AppenderMissingDatabaseOrTable,
        Error_AppenderExecSqlQueryFailed,
        Error_AppenderInvalidDatabaseLayout,
        Error_AppenderTelnetServerNotRunning,
        Error_AppenderAsyncDispatcherNotRunning,
        // QExtLogLevel
        Error_LevelStringInvalid,
        // Layouts, PatternFormatter
        Error_LayoutExpectedDigitFailed,
        Error_LayoutOptionIsNotPositive,
        Error_LayoutIntegerIsNotPositive,
        // Logger
        Error_LoggerInvalidLevelForRoot,
        // PropertyConfigurator, OptionHandler
        Error_ConfiguratorOpenFileFailed,
        Error_ConfiguratorReadFileFailed,
        Error_ConfiguratorInvalidSubstitution,
        Error_ConfiguratorInvalidOption,
        Error_ConfiguratorMissingAppender,
        Error_ConfiguratorUnknownAppenderClass,
        Error_ConfiguratorMissingLayout,
        Error_ConfiguratorUnknownLayoutClass,
        Error_ConfiguratorInvalidProperty,
        Error_ConfiguratorUnknownType
    };

    /*!
    * Creates an empty error. The error code is set to 0 and all other
    * members are set to be empty.
    *
    * \sa isEmpty()
    */
    QExtLogError();

    /*!
     * Creates an error with the Message \a message and the error code
     * \a code. The symbol for the error code is set to \a rSymbol and the
     * context to \a rContext.
     *
     * \a rContext must be string that can be converted to Latin-1. The
     * Latin-1 representation of the string is used with
     * QApplication::translate(), if a translation for \a message is
     * requested.
     *
     * \sa translatedMessage(), translatedMessageWithArgs()
     */
    explicit QExtLogError(const QString &message,
                      int code = 0,
                      const QString &symbol = QString(),
                      const QString &context = QString());

    /*!
     * Creates an error with the Message \a pMessage and the error code
     * \a code. The symbol for the error code is set to \a pSymbol and the
     * context to \a pContext.
     *
     * \a encoding specifies the encoding of \a pMessage. \a pSymbol and
     * \a pContext are expected to be Latin-1.
     *
     * \note To support the macros \ref Log4Qt::QEXT_LOG_ERROR "QEXT_LOG_ERROR"
     *       and \ref Log4Qt::QEXT_LOG_QCLASS_ERROR "QEXT_LOG_QCLASS_ERROR"
     *       the function tests, if \a pSymbol is the string representation of
     *       \a code. If it is, the symbol is set to be empty. Otherwise symbol
     *       is set to \a pSymbol.
     *
     * \sa translatedMessage(), translatedMessageWithArgs()
     */
    explicit QExtLogError(const char *message,
                      int code = 0,
                      const char *symbol = nullptr,
                      const char *context = nullptr,
                      EncodingEnum encoding = Encoding_Latin1);

    /*!
     * Returns the error code.
     *
     * \sa setCode()
     */
    int code() const;

    /*!
     * Returns the context for the error.
     *
     * \sa setContext()
     */
    QString context() const;

    /*!
     * Returns the error message.
     *
     * \sa setMessage()
     */
    QString message() const;

    /*!
     * Returns the symbol for the error code.
     *
     * \sa setSymbol()
     */
    QString symbol() const;

    /*!
     * Returns the translated error message.
     *
     * The translated message is created by calling
     * QCoreApplication::translate() using context().toLatin1() as
     * context and message.toUtf8() as message.
     *
     * \sa translatedMessageWithArgs()
     */
    QString translatedMessage() const;

    /*!
     * Sets the error code to \a code.
     *
     * \sa code()
     */
    void setCode(int code);

    /*!
     * Sets the context to \a className.
     *
     * \a rContext must be string that can be converted to Latin-1. The
    * Latin-1 representation of the string is used with
    * QApplication::translate(), if a translation for \a message is
    * requestd.
     *
    * \sa context(), translatedMessage(), translatedMessageWithArgs()
     */
    void setContext(const QString &className);

    /*!
     * Sets the error message to \a message
     *
     * \sa message()
     */
    void setMessage(const QString &message);

    /*!
     * Sets the symbol for the error code to \a symbol.
     *
     * \sa symbol()
     */
    void setSymbol(const QString &symbol);

    /*!
     * Returns the last error set for the current thread using
     * setLastError().
     *
     * \note: This function is thread-safe.
     *
     * \sa setLastError()
     */
    static QExtLogError lastError();

    /*!
     * Sets the last error for the current thread to \a logError.
     *
     * \note: This function is thread-safe.
     *
     * \sa lastError()
     */
    static void setLastError(const QExtLogError &logError);

    /*!
     * Appends \a rArg to the list of arguments and returns a reference to
     * this error.
     *
     * \sa operator<<(), args(), clearArgs()
     */
    QExtLogError &addArg(const QVariant &arg);

    /*!
     * This is an overloaded member function, provided for convenience.
     */
    QExtLogError &addArg(int arg);

    /*!
     * This is an overloaded member function, provided for convenience.
     */
    QExtLogError &addArg(const QString &arg);

    /*!
     * Appends \a logError to the list of causing errors and returns a
     * reference to this error.
     *
     * \sa causingErrors(), clearCausingErrors()
     */
    QExtLogError &addCausingError(const QExtLogError &logError);

    /*!
     * Returns the list of arguments that have been added to this error.
     *
     * \sa addArg(), operator<<(), clearArgs()
     */
    QList<QVariant> args() const;

    /*!
     * Returns the list of causing errors that have been added to this error.
     *
     * \sa addArg(), operator<<(), clearArgs()
     */
    QList<QExtLogError> causingErrors() const;

    /*!
     * Clears the list of arguments that have been added to this error.
     *
     * \sa addArg(), operator<<(), args()
     */
    void clearArgs();

    /*!
     * Clears the list of causing errors that have been added to this error.
     *
     * \sa addCausingError(), causingErrors()
     */
    void clearCausingErrors();

    /*!
     * Returns true, if the error code is 0 and the message is empty.
     * Otherwise it returns false.
     *
     * \sa code(), message()
     */
    bool isEmpty() const;

    /*!
     * Returns the message with arguments. The arguments are incoorporated
     * into the messag using QString::arg().
     *
     * \sa QString::arg(), translatedMessageWithArgs()
     */
    QString messageWithArgs() const;

    /*!
     * Returns the translated message with arguments. The arguments are
     * incoorporated into the messag using QString::arg().
     *
     * \sa QString::arg(), messageWithArgs(), translatedMessage()
     */
    QString translatedMessageWithArgs() const;

    /*!
     * Appends \a rArg to the list of arguments and returns a reference to
     * this error.
     *
     * \sa addArg()
     */
    QExtLogError &operator<<(const QVariant &arg);

    /*!
     * This is an overloaded member function, provided for convenience.
     */
    QExtLogError &operator<<(int arg);

    /*!
     * This is an overloaded member function, provided for convenience.
     */
    QExtLogError &operator<<(const QString &arg);

    /*!
     * Returns a string representation of the error.
     *
     * The string has the following format:
     *
     * <tt>
     * message (context::symbol, code): causing_error, causing_error
     * </tt>
     *
     * If members are empty they are omitted:
     * - Omit context, if empty
     * - Omit symbol, if empty
     * - Omit double colon with context and symbol, if both are empty
     * - Omit code, if 0
     * - Omit bracket with context/symbol and code, if all are empty
     * - Omit colon with causing errors, if no causing errors exist
     */
    QString toString() const;

private:
    QString insertArgs(const QString &message) const;
    QString cleanMessage(const QString &message);

private:
    int mCode;
    QString  mContext;
    QString  mMessage;
    QString  mSymbol;
    QList<QVariant> mArgs;
    QList<QExtLogError> mCausingErrors;

#ifndef QT_NO_DATASTREAM
    // Needs to be friend to stream objects
    friend QDataStream &operator<<(QDataStream &stream,
                                   const QExtLogError &logError);
    friend QDataStream &operator>>(QDataStream &stream,
                                   QExtLogError &logError);
#endif // QT_NO_DATASTREAM
};

#ifndef QT_NO_DATASTREAM
/*!
 * \relates QExtLogError
 *
 * Writes the given error \a logError to the given stream \a rStream,
 * and returns a reference to the stream.
 */
QDataStream &operator<<(QDataStream &stream,
                        const QExtLogError &logError);

/*!
 * \relates QExtLogError
 *
 * Reads an error from the given stream \a rStream into the given
 * error \a logError, and returns a reference to the stream.
 */
QDataStream &operator>>(QDataStream &stream,
                        QExtLogError &logError);
#endif // QT_NO_DATASTREAM

inline int QExtLogError::code() const
{
    return mCode;
}

inline QString QExtLogError::context() const
{
    return mContext;
}

inline QString QExtLogError::message() const
{
    return mMessage;
}

inline QString QExtLogError::symbol() const
{
    return mSymbol;
}

inline void QExtLogError::setCode(int code)
{
    mCode = code;
}

inline void QExtLogError::setContext(const QString &context)
{
    mContext = context;
}

inline void QExtLogError::setMessage(const QString &message)
{
    mMessage = cleanMessage(message);
}

inline void QExtLogError::setSymbol(const QString &symbol)
{
    mSymbol = symbol;
}

inline QExtLogError &QExtLogError::addArg(const QVariant &arg)
{
    mArgs << arg;
    return *this;
}

inline QExtLogError &QExtLogError::addArg(int arg)
{
    mArgs << QVariant(arg);
    return *this;
}

inline QExtLogError &QExtLogError::addArg(const QString &arg)
{
    mArgs << QVariant(arg);
    return *this;
}

inline QExtLogError &QExtLogError::addCausingError(const QExtLogError &logError)
{
    mCausingErrors << logError;
    return *this;
}

inline QList<QVariant> QExtLogError::args() const
{
    return mArgs;
}

inline void QExtLogError::clearArgs()
{
    mArgs.clear();
}

inline void QExtLogError::clearCausingErrors()
{
    mCausingErrors.clear();
}

inline QList<QExtLogError> QExtLogError::causingErrors() const
{
    return mCausingErrors;
}

inline bool QExtLogError::isEmpty() const
{
    return mCode || !mMessage.isEmpty();
}

inline QString QExtLogError::messageWithArgs() const
{
    return insertArgs(message());
}

inline QString QExtLogError::translatedMessageWithArgs() const
{
    return insertArgs(translatedMessage());
}

inline QExtLogError &QExtLogError::operator<<(const QVariant &arg)
{
    return addArg(arg);
}

inline QExtLogError &QExtLogError::operator<<(int arg)
{
    return addArg(arg);
}

inline QExtLogError &QExtLogError::operator<<(const QString &arg)
{
    return addArg(arg);
}

// } // namespace Log4Qt

Q_DECLARE_METATYPE(QExtLogError)
Q_DECLARE_TYPEINFO(QExtLogError, Q_MOVABLE_TYPE);

#endif // _QEXTLOGERROR_H
