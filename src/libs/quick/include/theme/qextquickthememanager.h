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

#ifndef QEXTQUICKTHEMEMANAGER_H
#define QEXTQUICKTHEMEMANAGER_H

#include <qextquickglobal.h>

#include <qextobject.h>

#include <QObject>
#include <QQmlEngine>
#include <QQuickWindow>



class QEXTQuickThemeBinder;
class QEXTQuickThemeHandler;
class QEXTQuickThemeManagerPrivate;
class QEXT_QUICK_API QEXTQuickThemeManager : public QObject, public QEXTObject
{
    Q_OBJECT
    Q_PROPERTY(bool generateThemeTemplateEnable READ isGenerateThemeTemplateEnable WRITE setGenerateThemeTemplateEnable)
    Q_PROPERTY(bool currentThemeValid READ isCurrentThemeValid NOTIFY currentThemeValidChanged)
    Q_PROPERTY(QVariantList themeList READ themeList NOTIFY themeListChanged)
    Q_PROPERTY(QString currentTheme READ currentTheme WRITE setCurrentTheme NOTIFY currentThemeChanged)

public:
    ~QEXTQuickThemeManager();
    static QObject *qmlSingletonTypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine);
    static QEXTQuickThemeManager *instance();

    bool isGenerateThemeTemplateEnable() const;
    bool isCurrentThemeValid() const;
    bool addThemeDir(const QString &themDir);
    bool addTheme(const QString &path);

    QVariantList themeList() const;
    QString currentTheme() const;
    QString startupTheme() const;
    QVariant getPropertyData(const QString &fieldKey, const QString &property);

    QString lastError() const;
    void generateThemeTemplateFile(QEXTQuickThemeBinder *binder = nullptr);

public Q_SLOTS:
    void setCurrentTheme(const QString &theme);
    void setStartupTheme(const QString &theme);
    void setGenerateThemeTemplateEnable(const bool &enable);

Q_SIGNALS:
    void themeListChanged();
    void currentThemeChanged();
    void currentThemeValidChanged();

private:
    friend class QEXTQuickThemeBinder;
    explicit QEXTQuickThemeManager(QObject *parent = nullptr);
    void newThemeBinder(QEXTQuickThemeBinder *binder);

private:
    QEXT_DECLARE_PRIVATE(QEXTQuickThemeManager)
    QEXT_DISABLE_COPY_MOVE(QEXTQuickThemeManager)
};



#endif // QEXTQUICKTHEMEMANAGER_H
