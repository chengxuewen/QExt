/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2025~Present ChengXueWen. Contact: 1398831004@qq.com.
** Copyright (C) 2007 - 2020 Log4Qt contributors
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
** documentation files (the "Software"), to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
** and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all copies or substantial portions
** of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
** CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
** IN THE SOFTWARE.
**
***********************************************************************************************************************/

#ifndef _QEXTLOGCONFIGURATORHELPER_H
#define _QEXTLOGCONFIGURATORHELPER_H

#include <qextLoggingEvent.h>

#include <QFileInfo>
#include <QObject>
#include <QMutex>
#include <QList>

class QFileSystemWatcher;

/*!
 * \brief The class QExtLogConfiguratorHelper provides a confiuration file watch
 *        and last error for configurator classes.
 *
 * A configuration file can be set using setConfigurationFile(). The file
 * is watched for changes. If a change occurs the configuration is reloaded
 * and the ConfigurationFileChanged() signal is Q_EMITted. Error information
 * for the last call to a configure function or the last configuration file
 * change can be accessed using configureError().
 *
 * \note All the functions declared in this class are thread-safe.
 */
class QEXT_LOGGING_API QExtLogConfiguratorHelper : public QObject
{
    Q_OBJECT

public:
    /*!
         * Prototype for a configure callback function. The function is called
         * when then configuration file is changed and takes the
         * configuration file as a parameter.
         *
         * \sa setConfigurationFile(),
         *     QExtLogPropertyConfigurator::configure(const QString &)
     */
    typedef bool (*ConfigureFunc)(const QString &fileName);

private:
    explicit QExtLogConfiguratorHelper(QObject *parent = QEXT_NULLPTR);
    virtual ~QExtLogConfiguratorHelper();

    QEXT_DISABLE_COPY_MOVE(QExtLogConfiguratorHelper)

public:

    /*!
     * Returns the error information for the last configuration operation
     * that took place. The configuration operation could be the result of
     * a call to one of the configure methods or through a change
     * to the configuration file.
     *
     * \sa setConfigureError(), QExtLogPropertyConfigurator::configure(),
     *     setConfigurationFile()
     */
    static QList<QExtLoggingEvent> configureError();

    /*!
     * Returns the current configuration file.
     *
     * \sa setConfigurationFile()
     */
    static QString configurationFile();

    /*!
         * Returns the QExtLogConfiguratorHelper instance.
         */
    static QExtLogConfiguratorHelper *instance();

    /*!
     * Sets the configuration error information for the last configuration
     * operation.
     *
     * \sa configureError()
     */
    static void setConfigureError(const QList<QExtLoggingEvent> &configureError);

    /*!
     * Sets the configuration file to \a fileName. The file is watched for
     * changes. On a file change the function \a pConfigureFunc will be called
     * and the signal configurationFileChange() will be Q_EMITted.
     *
     * Setting the configuration file to an empty string stops the file watch.
     *
     * \sa configurationFile(), QExtLogPropertyConfigurator::configureAndWatch(),
     *     configureError()
     */
    static void setConfigurationFile(const QString &fileName = QString(),
                                     ConfigureFunc pConfigureFunc = QEXT_NULLPTR);

Q_SIGNALS:
    /*!
     * The signal is Q_EMITted after a change to the file \a fileName
     * was processed. If an error occured during the configuration, the
     * flag \a error will be true and error information is available
     * over configureError().
     */
    void configurationFileChanged(const QString &fileName,
                                  bool error);

private Q_SLOTS:
    void doConfigurationFileChanged(const QString &fileName);
    void doConfigurationFileDirectoryChanged(const QString &path);
    void tryToReAddConfigurationFile();

private:
    void doSetConfigurationFile(const QString &fileName,
                                ConfigureFunc pConfigureFunc);

private:
    mutable QMutex mObjectGuard;
    QFileInfo mConfigurationFile;
    ConfigureFunc mConfigureFunc;
    QFileSystemWatcher *mConfigurationFileWatch;
    QList<QExtLoggingEvent> mConfigureError;
};

inline QList<QExtLoggingEvent> QExtLogConfiguratorHelper::configureError()
{
    QMutexLocker locker(&instance()->mObjectGuard);
    return instance()->mConfigureError;
}

inline QString QExtLogConfiguratorHelper::configurationFile()
{
    QMutexLocker locker(&instance()->mObjectGuard);
    return instance()->mConfigurationFile.absoluteFilePath();
}

inline void QExtLogConfiguratorHelper::setConfigureError(const QList<QExtLoggingEvent> &configureError)
{
    QMutexLocker locker(&instance()->mObjectGuard);
    instance()->mConfigureError = configureError;
}

inline void QExtLogConfiguratorHelper::setConfigurationFile(const QString &fileName,
        ConfigureFunc pConfigureFunc)
{
    instance()->doSetConfigurationFile(fileName, pConfigureFunc);
}

#endif // _QEXTLOGCONFIGURATORHELPER_H
