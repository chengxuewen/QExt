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

#ifndef _QEXTQMLTHEMEMANAGER_H
#define _QEXTQMLTHEMEMANAGER_H

#include <qextQmlThemeGlobal.h>
#include <qextQmlThemePalette.h>
#include <qextQmlSingleton.h>

#include <QObject>
#include <QQmlEngine>
#include <QQuickWindow>

class QExtQmlThemeBinder;
class QExtQmlThemeHandler;
class QExtQmlThemeManagerPrivate;
class QEXT_QMLTHEME_API QExtQmlThemeManager : public QExtQmlSingleton<QExtQmlThemeManager>
{
    Q_OBJECT
    QEXT_DECLARE_QML_SINGLETON(QExtQmlThemeManager)
    Q_PROPERTY(bool generateThemeTemplateEnable READ isGenerateThemeTemplateEnable WRITE setGenerateThemeTemplateEnable)
    Q_PROPERTY(bool currentThemeValid READ isCurrentThemeValid NOTIFY currentThemeValidChanged)
    Q_PROPERTY(QVariantList themeList READ themeList NOTIFY themeListChanged)
    Q_PROPERTY(QString currentTheme READ currentTheme WRITE setCurrentTheme NOTIFY currentThemeChanged)
    Q_PROPERTY(QExtQmlThemePalette* palette READ palette CONSTANT)

public:
    bool isGenerateThemeTemplateEnable() const;
    bool isCurrentThemeValid() const;
    bool addThemeDir(const QString &themDir);
    bool addTheme(const QString &path);

    QExtQmlThemePalette *palette();

    QVariantList themeList() const;
    QString currentTheme() const;
    QString startupTheme() const;
    QVariant getPropertyData(const QString &fieldKey, const QString &property);

    QString lastError() const;
    void generateThemeTemplateFile(QExtQmlThemeBinder *binder = nullptr);

    Q_INVOKABLE QString version() const override;
    void registerTypes(const char *url = nullptr) override;
    void initializeEngine(QQmlEngine *engine, const char *uri) override;

public Q_SLOTS:
    void setCurrentTheme(const QString &theme);
    void setStartupTheme(const QString &theme);
    void setGenerateThemeTemplateEnable(const bool &enable);

Q_SIGNALS:
    void themeListChanged();
    void currentThemeChanged();
    void currentThemeValidChanged();

protected:
    QExtQmlThemeManager();
    ~QExtQmlThemeManager() override;
    void newThemeBinder(QExtQmlThemeBinder *binder);

    QScopedPointer<QExtQmlThemeManagerPrivate> dd_ptr;

private:
    friend class QExtQmlThemeBinder;
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtQmlThemeManager)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQmlThemeManager)
};

#endif // _QEXTQMLTHEMEMANAGER_H
