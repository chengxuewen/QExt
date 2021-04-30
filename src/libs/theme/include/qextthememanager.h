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

#ifndef QTKSTYLEFRAMEWORK_H
#define QTKSTYLEFRAMEWORK_H

#include <qextobject.h>

#include <qextthemeglobal.h>

#include <QObject>
#include <QVariantList>

#ifdef QEXT_BUILD_QML
#include <QQmlEngine>
#include <QQuickWindow>
#endif

class QEXTThemeBinder;
class QEXTThemeHandler;
class QEXTThemeManagerPrivate;
class QEXT_THEME_API QEXTThemeManager : public QObject, public QEXTObject
{
    Q_OBJECT

    Q_PROPERTY(bool generateThemeTemplateEnable READ isGenerateThemeTemplateEnable WRITE setGenerateThemeTemplateEnable)
    Q_PROPERTY(bool currentThemeValid READ isCurrentThemeValid NOTIFY currentThemeValidChanged)
    Q_PROPERTY(QVariantList themeList READ themeNameList NOTIFY themeListChanged)
    Q_PROPERTY(QString currentTheme READ currentThemeName WRITE setCurrentTheme NOTIFY currentThemeChanged)

public:
    ~QEXTThemeManager();
#ifdef QEXT_BUILD_QML
    static QObject *qmlSingletonTypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine);
#endif

    static QEXTThemeManager *instance();

    bool isGenerateThemeTemplateEnable() const;
    bool isCurrentThemeValid() const;
    bool addThemeDir(const QString &themeDir);
    bool addTheme(const QString &themePath);

    void newThemeBinder(QEXTThemeBinder *binder);
    QVariantList themeNameList() const;
    QString currentThemeName() const;
    QString startupThemeName() const;
    QString lastError() const;
    QVariant propertyData(const QString &fieldKey, const QString &property);

    void generateThemeTemplateFile(QEXTThemeBinder *binder);

public Q_SLOTS:
    void setCurrentTheme(const QString &themeName);
    void setStartupTheme(const QString &themeName);
    void setGenerateThemeTemplateEnable(const bool &enable);
    void generateThemeTemplateFile();

protected Q_SLOTS:
    void onThemeFileChanged(const QString &filePath);

Q_SIGNALS:
    void themeListChanged();
    void currentThemeChanged();
    void currentThemeValidChanged();

protected:
    explicit QEXTThemeManager(QObject *parent = QEXT_NULLPTR);

private:
    QEXT_DECLARE_PRIVATE(QEXTThemeManager)
    QEXT_DISABLE_COPY_MOVE(QEXTThemeManager)
};

#endif // QTKSTYLEFRAMEWORK_H
