/****************************************************************************
**
** Library: QEXTQuick
**
** MIT License
**
** Copyright (c) 2019 toou http://www.toou.net
** Copyright (c) 2021 chengxuewen <1398831004@qq.com>
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

#ifndef QEXTQUICKWORLD_H
#define QEXTQUICKWORLD_H

#include <qextquickglobal.h>

#include <qextobject.h>

#include <QObject>
#include <QQuickItem>



/***
 * the class is very important in QEXTQuick
 * class can do some setup work:
 *  1.add theme file dir
 *  2.set app start up theme
 *  3.enable generate theme template json file to make some different theme file
 *
 * QEXTQuickWorld initilize the whole application system, so it must created in App ApplicationWindow.
 *
 * QML:
 * QEXTQuickWorld{
 *       appStartupTheme: "dark"
 *       appThemePaths:[
 *           "qrc:/themes/"
 *       ]
 * }
 * */
class QEXTQuickWorldPrivate;
class QEXT_QUICK_API QEXTQuickWorld : public QQuickItem, public QEXTObject
{
    Q_OBJECT

    Q_PROPERTY(QString startupTheme READ startupTheme WRITE setStartupTheme)
    Q_PROPERTY(QStringList themeDirs READ themeDirs WRITE setThemeDirs)
    Q_PROPERTY(bool generateThemeTemplateEnable READ isGenerateThemeTemplateEnable WRITE setGenerateThemeTemplateEnable)
    Q_PROPERTY(int mouseAreaCursorShape READ mouseAreaCursorShape WRITE setMouseAreaCursorShape)

public:
    explicit QEXTQuickWorld(QQuickItem* parent = QEXT_DECL_NULLPTR);
    ~QEXTQuickWorld();

    QStringList themeDirs() const;
    void setThemeDirs(const QStringList &themeDirs);

    QString startupTheme() const;
    void setStartupTheme(const QString &themeName);

    int mouseAreaCursorShape() const;
    void setMouseAreaCursorShape(const int &iShape);

    bool isGenerateThemeTemplateEnable() const;
    void setGenerateThemeTemplateEnable(const bool &enable);

protected Q_SLOTS:
    void onParentChanged(QQuickItem *parent);

private:
    QEXT_DECL_PRIVATE(QEXTQuickWorld)
    QEXT_DISABLE_COPY_MOVE(QEXTQuickWorld)
};



#endif // QEXTQUICKWORLD_H
