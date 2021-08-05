/****************************************************************************
**
** Library: QEXTQuick
**
** MIT License
**
** Copyright (c) 2021 chengxuewen <1398831004@qq.com>
** Copyright (c) 2019 toou http://www.toou.net
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all
** copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
****************************************************************************/
#include <qextquickthememanager.h>
#include <qextquickthememanager_p.h>
#include <qextquickthemebinder.h>
#include <qextquickthemehandler.h>
#include <qextquickthemeconstant.h>
#include <qextquickthemefileparser.h>
#include <qextquickthemejsonfileparser.h>

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



QEXTQuickThemeManagerPrivate::QEXTQuickThemeManagerPrivate(QEXTQuickThemeManager *qq)
    : QEXTObjectPrivate(qq)
{
    m_generateThemeTemplateEnable = false;
}

QEXTQuickThemeManagerPrivate::~QEXTQuickThemeManagerPrivate()
{
    qDeleteAll(m_themeNameToHandlerMap);
    m_themeNameToHandlerMap.clear();
}



static QEXTQuickThemeManager *sm_instance = nullptr;

QEXTQuickThemeManager::QEXTQuickThemeManager(QObject *parent)
    : QObject(parent), QEXTObject(*(new QEXTQuickThemeManagerPrivate(this)))
{
    QEXT_D(QEXTQuickThemeManager);
    d->m_themeFileParser.reset(new QEXTQuickThemeJsonFileParser());
    d->m_fileSystemWatcher.reset(new QFileSystemWatcher(this));
    connect(d->m_fileSystemWatcher.data(), &QFileSystemWatcher::fileChanged, [=](const QString &path) {
        qDebug() << "path:" << path;
        QFileInfo fileInfo(path);
        QTimer::singleShot(100, [=]() {
            this->addTheme(fileInfo.absoluteFilePath());
        });
    });
}

void QEXTQuickThemeManager::newThemeBinder(QEXTQuickThemeBinder *binder)
{
    connect(binder, &QEXTQuickThemeBinder::initialized, [=]() {
        this->generateThemeTemplateFile();
    });
    connect(binder, &QEXTQuickThemeBinder::parentChanged, [=]() {
        this->generateThemeTemplateFile();
    });
}

QEXTQuickThemeManager::~QEXTQuickThemeManager()
{

}

QObject *QEXTQuickThemeManager::qmlSingletonTypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return QEXTQuickThemeManager::instance();
}

QEXTQuickThemeManager *QEXTQuickThemeManager::instance()
{
    static QMutex mutex;
    QMutexLocker mutexLocker(&mutex);
    if (nullptr == sm_instance) {
        sm_instance = new QEXTQuickThemeManager();
    }
    return sm_instance;
}

bool QEXTQuickThemeManager::isGenerateThemeTemplateEnable() const
{
    QEXT_DC(QEXTQuickThemeManager);
    return d->m_generateThemeTemplateEnable;
}

bool QEXTQuickThemeManager::isCurrentThemeValid() const
{
    QEXT_DC(QEXTQuickThemeManager);
    return d->m_themeNameToHandlerMap.contains(d->m_currentThemeName);
}

bool QEXTQuickThemeManager::addThemeDir(const QString &themDir)
{
    QEXT_D(QEXTQuickThemeManager);
    QDir dir(themDir);
    if (!dir.exists()) {
        d->m_lastErrorString = QString("add theme dir failed for %1 dir not exist!").arg(themDir);
        qWarning() << d->m_lastErrorString;
        return false;
    }

    bool ret = true;
    QStringList listFileFilters;
    listFileFilters << "*.json";
    QFileInfoList listFileInfo = dir.entryInfoList(listFileFilters, QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    foreach (QFileInfo fileInfo, listFileInfo) {
        ret = ret && this->addTheme(fileInfo.absoluteFilePath());
        if (ret) {
            d->m_fileSystemWatcher->addPath(fileInfo.filePath());
        }
    }
    if(!d->m_startupThemeName.isEmpty() && d->m_themeNameToHandlerMap.contains(d->m_startupThemeName)){
        this->setCurrentTheme(d->m_startupThemeName);
    }
    return ret;
}

bool QEXTQuickThemeManager::addTheme(const QString &path)
{
    QEXT_D(QEXTQuickThemeManager);
    QString errorString;
    QMap<QString, QVariantMap> data;
    bool ret = d->m_themeFileParser->parseThemeFile(path, data, errorString);
    if (!ret) {
        qWarning() << "Theme file strPath parse failed for " << errorString;
        return false;
    }

    QString name = data.value(QEXTQuickThemeConstant::THEME_INFO_KEY).value(QEXTQuickThemeConstant::THEME_INFO_NAME_KEY).toString();
    QEXTQuickThemeHandler *handler = new QEXTQuickThemeHandler(name, path);
    handler->setThemeData(data);
    if (d->m_themeNameToHandlerMap.contains(name)) {
        d->m_themeNameToHandlerMap.value(name)->deleteLater();
        d->m_themeNameToHandlerMap.remove(name);
    }
    d->m_themeNameToHandlerMap.insert(name, handler);
    if (name == d->m_currentThemeName) {
        emit this->currentThemeChanged();
    }
    emit this->themeListChanged();
    return true;
}

QVariantList QEXTQuickThemeManager::themeList() const
{
    QEXT_DC(QEXTQuickThemeManager);
    QVariantList list;
    foreach (QEXTQuickThemeHandler *themeHandler, d->m_themeNameToHandlerMap.values()) {
        list.append(themeHandler->themeInfo());
    }
    return list;
}

QString QEXTQuickThemeManager::currentTheme() const
{
    QEXT_DC(QEXTQuickThemeManager);
    return d->m_currentThemeName;
}

QString QEXTQuickThemeManager::startupTheme() const
{
    QEXT_DC(QEXTQuickThemeManager);
    return d->m_startupThemeName;
}

QString QEXTQuickThemeManager::lastError() const
{
    QEXT_DC(QEXTQuickThemeManager);
    return d->m_lastErrorString;
}

QVariant QEXTQuickThemeManager::getPropertyData(const QString &fieldKey, const QString &property)
{
    QEXT_D(QEXTQuickThemeManager);
    if (!this->isCurrentThemeValid()) {
        qWarning() << "Current theme is invalid, can not get property data!";
        return QVariant();
    }
    QEXTQuickThemeHandler *handler = d->m_themeNameToHandlerMap.value(d->m_currentThemeName);
    if (nullptr == handler) {
        qCritical() << "Current theme handler pointer is nullptr, can not get property data!";
        return QVariant();
    }
    return handler->propertyData(fieldKey, property);
}

void QEXTQuickThemeManager::generateThemeTemplateFile(QEXTQuickThemeBinder *binder)
{
    QEXT_D(QEXTQuickThemeManager);
    if (!d->m_generateThemeTemplateEnable) {
        return;
    }
    static QString errorString;
    static bool ret = true;
    if (!ret) {
        return;
    }
    ret = d->m_themeFileParser->generateThemeTemplateFile(errorString, binder);
    if (!ret) {
        qWarning() << "Generate theme template file for " << errorString;
        return;
    }
}

void QEXTQuickThemeManager::setCurrentTheme(const QString &theme)
{
    QEXT_D(QEXTQuickThemeManager);
    if (theme != d->m_currentThemeName) {
        if (d->m_themeNameToHandlerMap.contains(theme)) {
            d->m_currentThemeName = theme;
            emit this->currentThemeChanged();
        }
    }
}

void QEXTQuickThemeManager::setStartupTheme(const QString &theme)
{
    QEXT_D(QEXTQuickThemeManager);
    if (!d->m_currentThemeName.isEmpty()) {
        qWarning() << "App startup theme has been set as " << d->m_currentThemeName;
        return;
    }
    d->m_currentThemeName = theme;
    this->setCurrentTheme(theme);
}

void QEXTQuickThemeManager::setGenerateThemeTemplateEnable(const bool &enable)
{
    QEXT_D(QEXTQuickThemeManager);
    if (enable != d->m_generateThemeTemplateEnable) {
        d->m_generateThemeTemplateEnable = enable;
    }
}
