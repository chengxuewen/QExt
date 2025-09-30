/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2021 ChengXueWen.
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

#include <qextQmlThemeManager.h>
#include <qextQmlThemeBinder.h>
#include <qextQmlThemeHandler.h>
#include <qextQmlThemePalette.h>
#include <qextQmlThemeConstant.h>
#include <qextQmlThemeFileParser.h>
#include <qextQmlThemeJsonFileParser.h>

#include <QMutex>
#include <QMutexLocker>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QTimer>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileInfoList>
#include <QFileSystemWatcher>

class QFileSystemWatcher;

class QExtQmlThemeHandler;
class QExtQmlThemeFileParser;
class QExtQmlThemeManager;
class QEXT_QMLTHEME_API QExtQmlThemeManagerPrivate
{
    Q_DISABLE_COPY(QExtQmlThemeManagerPrivate)
    Q_DECLARE_PUBLIC(QExtQmlThemeManager)
public:
    explicit QExtQmlThemeManagerPrivate(QExtQmlThemeManager *q);
    virtual ~QExtQmlThemeManagerPrivate();

    QExtQmlThemeManager * const q_ptr;

    QScopedPointer<QFileSystemWatcher> mFileSystemWatcher;
    QScopedPointer<QExtQmlThemeFileParser> mThemeFileParser;
    QMap<QString, QExtQmlThemeHandler *> mThemeNameToHandlerMap;
    bool mGenerateThemeTemplateEnable;
    QExtQmlThemePalette mPalette;
    QString mStartupThemeName;
    QString mCurrentThemeName;
    QString mLastErrorString;
};
QExtQmlThemeManagerPrivate::QExtQmlThemeManagerPrivate(QExtQmlThemeManager *q)
    : q_ptr(q)
{
    mGenerateThemeTemplateEnable = false;
}

QExtQmlThemeManagerPrivate::~QExtQmlThemeManagerPrivate()
{
    qDeleteAll(mThemeNameToHandlerMap);
    mThemeNameToHandlerMap.clear();
}

QExtQmlThemeManager::QExtQmlThemeManager()
    : dd_ptr(new QExtQmlThemeManagerPrivate(this))
{
    Q_D(QExtQmlThemeManager);
    d->mThemeFileParser.reset(new QExtQmlThemeJsonFileParser);
    d->mFileSystemWatcher.reset(new QFileSystemWatcher(this));
    connect(d->mFileSystemWatcher.data(), &QFileSystemWatcher::fileChanged, this, [this](const QString &path)
            {
                qDebug() << "path:" << path;
                QFileInfo fileInfo(path);
                QTimer::singleShot(100, [=]()
                                   {
                                       this->addTheme(fileInfo.absoluteFilePath());
                                   });
            });
}

void QExtQmlThemeManager::newThemeBinder(QExtQmlThemeBinder *binder)
{
    connect(binder, &QExtQmlThemeBinder::initialized, this, [this]()
            {
                this->generateThemeTemplateFile();
            });
    connect(binder, &QExtQmlThemeBinder::parentChanged, this, [this]()
            {
                this->generateThemeTemplateFile();
            });
}

QExtQmlThemeManager::~QExtQmlThemeManager()
{
}

bool QExtQmlThemeManager::isGenerateThemeTemplateEnable() const
{
    Q_D(const QExtQmlThemeManager);
    return d->mGenerateThemeTemplateEnable;
}

bool QExtQmlThemeManager::isCurrentThemeValid() const
{
    Q_D(const QExtQmlThemeManager);
    return d->mThemeNameToHandlerMap.contains(d->mCurrentThemeName);
}

bool QExtQmlThemeManager::addThemeDir(const QString &themDir)
{
    Q_D(QExtQmlThemeManager);
    QDir dir(themDir);
    if (!dir.exists())
    {
        d->mLastErrorString = QString("add theme dir failed for %1 dir not exist!").arg(themDir);
        qWarning() << d->mLastErrorString;
        return false;
    }

    bool ret = true;
    QStringList listFileFilters;
    listFileFilters << "*.json";
    QFileInfoList listFileInfo = dir.entryInfoList(listFileFilters, QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    foreach (QFileInfo fileInfo, listFileInfo)
    {
        ret = ret && this->addTheme(fileInfo.absoluteFilePath());
        if (ret)
        {
            d->mFileSystemWatcher->addPath(fileInfo.filePath());
        }
    }
    if(!d->mStartupThemeName.isEmpty() && d->mThemeNameToHandlerMap.contains(d->mStartupThemeName))
    {
        this->setCurrentTheme(d->mStartupThemeName);
    }
    return ret;
}

bool QExtQmlThemeManager::addTheme(const QString &path)
{
    Q_D(QExtQmlThemeManager);
    QString errorString;
    QMap<QString, QVariantMap> data;
    bool ret = d->mThemeFileParser->parseThemeFile(path, data, errorString);
    if (!ret)
    {
        qWarning() << "Theme file strPath parse failed for " << errorString;
        return false;
    }

    QString name = data.value(QExtQmlThemeConstant::kInfo).value(QExtQmlThemeConstant::kInfoName).toString();
    QExtQmlThemeHandler *handler = new QExtQmlThemeHandler(name, path);
    handler->setThemeData(data);
    if (d->mThemeNameToHandlerMap.contains(name))
    {
        d->mThemeNameToHandlerMap.value(name)->deleteLater();
        d->mThemeNameToHandlerMap.remove(name);
    }
    d->mThemeNameToHandlerMap.insert(name, handler);
    if (name == d->mCurrentThemeName)
    {
        emit this->currentThemeChanged();
    }
    emit this->themeListChanged();
    return true;
}

QExtQmlThemePalette *QExtQmlThemeManager::palette()
{
    Q_D(QExtQmlThemeManager);
    return &d->mPalette;
}

QVariantList QExtQmlThemeManager::themeList() const
{
    Q_D(const QExtQmlThemeManager);
    QVariantList list;
    foreach (QExtQmlThemeHandler *themeHandler, d->mThemeNameToHandlerMap.values())
    {
        list.append(themeHandler->themeInfo());
    }
    return list;
}

QString QExtQmlThemeManager::currentTheme() const
{
    Q_D(const QExtQmlThemeManager);
    return d->mCurrentThemeName;
}

QString QExtQmlThemeManager::startupTheme() const
{
    Q_D(const QExtQmlThemeManager);
    return d->mStartupThemeName;
}

QString QExtQmlThemeManager::lastError() const
{
    Q_D(const QExtQmlThemeManager);
    return d->mLastErrorString;
}

QVariant QExtQmlThemeManager::getPropertyData(const QString &fieldKey, const QString &property)
{
    Q_D(QExtQmlThemeManager);
    if (!this->isCurrentThemeValid())
    {
        qWarning() << "Current theme is invalid, can not get property data!";
        return QVariant();
    }
    QExtQmlThemeHandler *handler = d->mThemeNameToHandlerMap.value(d->mCurrentThemeName);
    if (nullptr == handler)
    {
        qCritical() << "Current theme handler pointer is nullptr, can not get property data!";
        return QVariant();
    }
    return handler->propertyData(fieldKey, property);
}

void QExtQmlThemeManager::generateThemeTemplateFile(QExtQmlThemeBinder *binder)
{
    Q_D(QExtQmlThemeManager);
    if (!d->mGenerateThemeTemplateEnable)
    {
        return;
    }
    static QString errorString;
    static bool ret = true;
    if (!ret)
    {
        return;
    }
    ret = d->mThemeFileParser->generateThemeTemplateFile(errorString, binder);
    if (!ret)
    {
        qWarning() << "Generate theme template file for " << errorString;
        return;
    }
}

QString QExtQmlThemeManager::version() const
{
    return QString("%1.%2").arg(QEXT_VERSION_MAJOR).arg(QEXT_VERSION_MAJOR);
}

void QExtQmlThemeManager::registerTypes(const char *url)
{
    qDebug() << QString("QExtQmlThemeManager::registerTypes(%1)").arg(QEXT_QML_MODULE_URI);
    if (url)
    {
        Q_ASSERT(url == QLatin1String(QEXT_QML_MODULE_URI));
    }
    static QExtOnceFlag onceFlag;
    if (onceFlag.enter())
    {
        Q_INIT_RESOURCE(qextQmlTheme);
        int major = QEXT_VERSION_MAJOR;
        int minor = QEXT_VERSION_MINOR;

        qmlRegisterType<QExtQmlThemeBinder>(QEXT_QML_MODULE_URI, major, minor, "QExtQmlThemeBinder");
        qmlRegisterType<QExtQmlThemePalette>(QEXT_QML_MODULE_URI, major, minor, "QExtQmlThemePalette");
        qmlRegisterSingletonType<QExtQmlThemeManager>(QEXT_QML_MODULE_URI, major, minor, "QExtQmlThemeManager",
                                                      QExtQmlThemeManager::create);
        onceFlag.leave();
    }
}

void QExtQmlThemeManager::initializeEngine(QQmlEngine *engine, const char *uri)
{

}

void QExtQmlThemeManager::setCurrentTheme(const QString &theme)
{
    Q_D(QExtQmlThemeManager);
    if (theme != d->mCurrentThemeName)
    {
        if (d->mThemeNameToHandlerMap.contains(theme))
        {
            d->mCurrentThemeName = theme;
            emit this->currentThemeChanged();
        }
    }
}

void QExtQmlThemeManager::setStartupTheme(const QString &theme)
{
    Q_D(QExtQmlThemeManager);
    if (!d->mCurrentThemeName.isEmpty())
    {
        qWarning() << "App startup theme has been set as " << d->mCurrentThemeName;
        return;
    }
    d->mCurrentThemeName = theme;
    this->setCurrentTheme(theme);
}

void QExtQmlThemeManager::setGenerateThemeTemplateEnable(const bool &enable)
{
    Q_D(QExtQmlThemeManager);
    if (enable != d->mGenerateThemeTemplateEnable)
    {
        d->mGenerateThemeTemplateEnable = enable;
    }
}
