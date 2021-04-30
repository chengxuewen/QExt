/****************************************************************************
**
** Library: QEXTQuick
**
** MIT License
**
** Copyright (c) 2019 toou http://www.toou.net
** Copyright (c) 2020 chengxuewen <1398831004@qq.com>
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

#include <qextthememanager.h>
#include <qextthememanager_p.h>
#include <qextthemebinder.h>
#include <qextthemehandler.h>
#include <qextthemeconstant.h>
#include <qextthemefileparserbase.h>
#include <qextthemejsonfileparser.h>

#include <QMutex>
#include <QMutexLocker>
#include <QTimer>
#include <QDir>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QFileInfoList>
#include <QFileSystemWatcher>

#ifdef QEXT_BUILD_QML
#include <QQmlComponent>
#include <QQmlEngine>
#endif

QEXTThemeManagerPrivate::QEXTThemeManagerPrivate(QEXTThemeManager *qq)
    : QEXTObjectPrivate(qq)
{
    m_themeFileParser.reset(new QEXTThemeJsonFileParser);
    m_fileSystemWatcher.reset(new QFileSystemWatcher);
    m_generateThemeTemplateEnable = false;
}

QEXTThemeManagerPrivate::~QEXTThemeManagerPrivate()
{
    qDeleteAll(m_themeHandlerMap);
    m_themeHandlerMap.clear();
}



static QEXTThemeManager *sm_instance = QEXT_NULLPTR;

QEXTThemeManager::QEXTThemeManager(QObject *parent)
    : QObject(parent), QEXTObject(*(new QEXTThemeManagerPrivate(this)))
{
    QEXT_D(QEXTThemeManager);
    connect(d->m_fileSystemWatcher.data(), SIGNAL(fileChanged(QString)), this, SLOT(onThemeFileChanged(QString)));
}

void QEXTThemeManager::newThemeBinder(QEXTThemeBinder *binder)
{
    connect(binder, SIGNAL(initialized()), this, SLOT(generateThemeTemplateFile()));
    connect(binder, SIGNAL(parentChanged()), this, SLOT(generateThemeTemplateFile()));
}

QEXTThemeManager::~QEXTThemeManager()
{

}

#ifdef QEXT_BUILD_QML
QObject *QEXTThemeManager::qmlSingletonTypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return QEXTThemeManager::instance();
}
#endif

QEXTThemeManager *QEXTThemeManager::instance()
{
    static QMutex mutex;
    QMutexLocker mutexLocker(&mutex);
    if (QEXT_NULLPTR == sm_instance) {
        sm_instance = new QEXTThemeManager();
    }
    return sm_instance;
}

bool QEXTThemeManager::isGenerateThemeTemplateEnable() const
{
    QEXT_DC(QEXTThemeManager);
    return d->m_generateThemeTemplateEnable;
}

bool QEXTThemeManager::isCurrentThemeValid() const
{
    QEXT_DC(QEXTThemeManager);
    return d->m_themeHandlerMap.contains(d->m_currentThemeName);
}

bool QEXTThemeManager::addThemeDir(const QString &themeDir)
{
    QEXT_D(QEXTThemeManager);
    QDir dir(themeDir);
    if (!dir.exists()) {
        d->m_lastError = QString("add theme dir failed for %1 dir not exist!").arg(themeDir);
        qWarning() << d->m_lastError;
        return false;
    }

    bool success = true;
    QStringList listFileFilters;
    listFileFilters << "*.json";
    QFileInfoList listFileInfo = dir.entryInfoList(listFileFilters, QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    foreach (QFileInfo fileInfo, listFileInfo) {
        success = success && this->addTheme(fileInfo.absoluteFilePath());
        if (success) {
            d->m_fileSystemWatcher->addPath(fileInfo.filePath());
        }
    }
    if(!d->m_startupThemeName.isEmpty() && d->m_themeHandlerMap.contains(d->m_startupThemeName)){
        this->setCurrentTheme(d->m_startupThemeName);
    }
    return success;
}

bool QEXTThemeManager::addTheme(const QString &themePath)
{
    QEXT_D(QEXTThemeManager);
    QString errorString;
    QMap<QString, QVariantMap> themeData;
    bool success = d->m_themeFileParser->parseThemeFile(themePath, themeData, errorString);
    if (!success) {
        qWarning() << "Theme file strPath parse failed for " << errorString;
        return false;
    }

    QString nameString = themeData.value(QEXTThemeConstant::THEME_INFO_KEY).value(QEXTThemeConstant::THEME_INFO_NAME_KEY).toString();
    QEXTThemeHandler *handler = new QEXTThemeHandler(nameString, themePath);
    handler->setThemeData(themeData);
    if (d->m_themeHandlerMap.contains(nameString)) {
        d->m_themeHandlerMap.value(nameString)->deleteLater();
        d->m_themeHandlerMap.remove(nameString);
    }
    d->m_themeHandlerMap.insert(nameString, handler);
    if (nameString == d->m_currentThemeName) {
        emit this->currentThemeChanged();
    }
    emit this->themeListChanged();
    return true;
}

QVariantList QEXTThemeManager::themeNameList() const
{
    QEXT_DC(QEXTThemeManager);
    QVariantList list;
    foreach (QEXTThemeHandler *themeHandler, d->m_themeHandlerMap.values()) {
        list.append(themeHandler->themeInfo());
    }
    return list;
}

QString QEXTThemeManager::currentThemeName() const
{
    QEXT_DC(QEXTThemeManager);
    return d->m_currentThemeName;
}

QString QEXTThemeManager::startupThemeName() const
{
    QEXT_DC(QEXTThemeManager);
    return d->m_startupThemeName;
}

QString QEXTThemeManager::lastError() const
{
    QEXT_DC(QEXTThemeManager);
    return d->m_lastError;
}

QVariant QEXTThemeManager::propertyData(const QString &fieldKey, const QString &property)
{
    QEXT_D(QEXTThemeManager);
    if (!this->isCurrentThemeValid()) {
        qWarning() << "Current theme is invalid, can not get property data!";
        return QVariant();
    }
    QEXTThemeHandler *handler = d->m_themeHandlerMap.value(d->m_currentThemeName);
    if (QEXT_NULLPTR == handler) {
        qCritical() << "Current theme handler pointer is nullptr, can not get property data!";
        return QVariant();
    }
    return handler->propertyData(fieldKey, property);
}

void QEXTThemeManager::generateThemeTemplateFile(QEXTThemeBinder *binder)
{
    QEXT_D(QEXTThemeManager);
    if (!d->m_generateThemeTemplateEnable) {
        return;
    }
    static QString errorString;
    static bool success = true;
    if (!success) {
        return;
    }
    success = d->m_themeFileParser->generateThemeTemplateFile(errorString, binder);
    if (!success) {
        qWarning() << "Generate theme template file for " << errorString;
        return;
    }
}

void QEXTThemeManager::setCurrentTheme(const QString &themeName)
{
    QEXT_D(QEXTThemeManager);
    if (themeName != d->m_currentThemeName) {
        if (d->m_themeHandlerMap.contains(themeName)) {
            d->m_currentThemeName = themeName;
            emit this->currentThemeChanged();
        }
    }
}

void QEXTThemeManager::setStartupTheme(const QString &themeName)
{
    QEXT_D(QEXTThemeManager);
    if (!d->m_currentThemeName.isEmpty()) {
        qWarning() << "App startup theme has been set as " << d->m_currentThemeName;
        return;
    }
    d->m_currentThemeName = themeName;
    this->setCurrentTheme(themeName);
}

void QEXTThemeManager::setGenerateThemeTemplateEnable(const bool &enable)
{
    QEXT_D(QEXTThemeManager);
    if (enable != d->m_generateThemeTemplateEnable) {
        d->m_generateThemeTemplateEnable = enable;
    }
}

void QEXTThemeManager::generateThemeTemplateFile()
{
    this->generateThemeTemplateFile(QEXT_NULLPTR);
}

void QEXTThemeManager::onThemeFileChanged(const QString &filePath)
{
    qDebug() << "filePath:" << filePath;
    QFileInfo fileInfo(filePath);
    QTimer::singleShot(100, [=]() {
        this->addTheme(fileInfo.absoluteFilePath());
    });
}
