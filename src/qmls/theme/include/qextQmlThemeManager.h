/****************************************************************************
**
** Library: QEXTQmlQuick
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

#ifndef _QEXTQMLTHEMEMANAGER_H
#define _QEXTQMLTHEMEMANAGER_H

#include <qextQmlThemeGlobal.h>

#include <QObject>
#include <QQmlEngine>
#include <QQuickWindow>

class QEXTQmlThemeBinder;
class QEXTQmlThemeHandler;
class QEXTQmlThemeManagerPrivate;
class QEXT_QMLTHEME_API QEXTQmlThemeManager : public QObject
{
    Q_OBJECT
    QEXT_DECL_PRIVATE_D(dd_ptr, QEXTQmlThemeManager)
    Q_DISABLE_COPY(QEXTQmlThemeManager)

    Q_PROPERTY(bool generateThemeTemplateEnable READ isGenerateThemeTemplateEnable WRITE setGenerateThemeTemplateEnable)
    Q_PROPERTY(bool currentThemeValid READ isCurrentThemeValid NOTIFY currentThemeValidChanged)
    Q_PROPERTY(QVariantList themeList READ themeList NOTIFY themeListChanged)
    Q_PROPERTY(QString currentTheme READ currentTheme WRITE setCurrentTheme NOTIFY currentThemeChanged)

public:
    ~QEXTQmlThemeManager();
    static QObject *qmlSingletonTypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine);
    static QEXTQmlThemeManager *instance();

    bool isGenerateThemeTemplateEnable() const;
    bool isCurrentThemeValid() const;
    bool addThemeDir(const QString &themDir);
    bool addTheme(const QString &path);

    QVariantList themeList() const;
    QString currentTheme() const;
    QString startupTheme() const;
    QVariant getPropertyData(const QString &fieldKey, const QString &property);

    QString lastError() const;
    void generateThemeTemplateFile(QEXTQmlThemeBinder *binder = nullptr);

public Q_SLOTS:
    void setCurrentTheme(const QString &theme);
    void setStartupTheme(const QString &theme);
    void setGenerateThemeTemplateEnable(const bool &enable);

Q_SIGNALS:
    void themeListChanged();
    void currentThemeChanged();
    void currentThemeValidChanged();

private:
    friend class QEXTQmlThemeBinder;
    explicit QEXTQmlThemeManager(QObject *parent = nullptr);
    void newThemeBinder(QEXTQmlThemeBinder *binder);

protected:
    QScopedPointer<QEXTQmlThemeManagerPrivate> dd_ptr;
};

#endif // _QEXTQMLTHEMEMANAGER_H
