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

#ifndef _QEXTLOGPROPERTYCONFIGURATOR_H
#define _QEXTLOGPROPERTYCONFIGURATOR_H

#include <qextLogLayout.h>
#include <qextLogAppender.h>

#include <QHash>

class QSettings;

class QExtLogger;
class QExtLogProperties;
class QExtLogListAppender;
class QExtLoggerRepository;

/*!
 * \brief The class QExtLogPropertyConfigurator allows the configuration of the
 *        package from a JAVA properties file.
 *
 * \note All the functions declared in this class are thread-safe.
 */
class QEXT_LOGGING_API QExtLogPropertyConfigurator
{
public:
    QExtLogPropertyConfigurator();

private:
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtLogPropertyConfigurator)

public:
    /*!
     * \sa QExtLogConfiguratorHelper::configureError()
     */
    bool doConfigure(const QExtLogProperties &properties,
                     QExtLoggerRepository *loggerRepository = QEXT_NULLPTR);

    /*!
     * \sa QExtLogConfiguratorHelper::configureError()
     */
    bool doConfigure(const QString &configFileName,
                     QExtLoggerRepository *loggerRepository = QEXT_NULLPTR);

    /*!
     * Reads the configuration data from the QSettings object
     * \a settings.
     *
     * \sa \ref QExtLogProperties::load(const QSettings &) "QExtLogProperties::load()",
     *     QExtLogConfiguratorHelper::configureError()
     */
    bool doConfigure(const QSettings &settings,
                     QExtLoggerRepository *loggerRepository = QEXT_NULLPTR);


    /*!
     * \sa QExtLogConfiguratorHelper::configureError()
     */
    static bool configure(const QExtLogProperties &properties);

    /*!
     * \sa QExtLogConfiguratorHelper::configureError()
     */
    static bool configure(const QString &configFilename);

    /*!
     * Reads the configuration data from the QSettings object
     * \a settings.
     *
     * \sa \ref doConfigure(const QSettings &, QExtLoggerRepository *) "doConfigure()",
     *     \ref QExtLogProperties::load(const QSettings &) "QExtLogProperties::load()",
     *     QExtLogConfiguratorHelper::configureError()
     */
    static bool configure(const QSettings &settings);

    /*!
     * \sa QExtLogConfiguratorHelper::configureError(),
     *     QExtLogConfiguratorHelper::configurationFile()
     */
    static bool configureAndWatch(const QString &configFilename);

private:
    void configureFromFile(const QString &configFileName,
                           QExtLoggerRepository *loggerRepository);
    void configureFromProperties(const QExtLogProperties &properties,
                                 QExtLoggerRepository *loggerRepository);
    void configureFromSettings(const QSettings &settings,
                               QExtLoggerRepository *loggerRepository);
    void configureGlobalSettings(const QExtLogProperties &properties,
                                 QExtLoggerRepository *loggerRepository) const;
    void configureNonRootElements(const QExtLogProperties &properties,
                                  QExtLoggerRepository *loggerRepository);
    void configureRootLogger(const QExtLogProperties &properties,
                             QExtLoggerRepository *loggerRepository);
    void parseAdditivityForLogger(const QExtLogProperties &properties,
                                  QExtLogger *logger,
                                  const QString &log4jName) const;
    QExtLogAppenderSharedPtr parseAppender(const QExtLogProperties &properties,
                                    const QString &name);
    QExtLogLayoutSharedPtr parseLayout(const QExtLogProperties &properties,
                                const QString &appendename);
    void parseLogger(const QExtLogProperties &properties,
                     QExtLogger *logger,
                     const QString &key,
                     const QString &value);
    void setProperties(const QExtLogProperties &properties,
                       const QString &prefix,
                       const QStringList &exclusion,
                       QObject *object);
    void startCaptureErrors();
    bool stopCaptureErrors();

private:
    QExtLogAppenderSharedPtr mpConfigureErrors;
    QHash<QString, QExtLogAppenderSharedPtr> mAppenderRegistry;
};

inline QExtLogPropertyConfigurator::QExtLogPropertyConfigurator()
{}

#endif // _QEXTLOGPROPERTYCONFIGURATOR_H
