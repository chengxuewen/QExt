#ifndef _QEXTQUICKWORLD_H
#define _QEXTQUICKWORLD_H

#include <qextQuickGlobal.h>

#include <QObject>
#include <QQuickItem>
#include <QScopedPointer>

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
class QEXT_QUICK_API QEXTQuickWorld : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(QEXTQuickWorld)
    Q_DECLARE_PRIVATE_D(dd_ptr, QEXTQuickWorld)

    Q_PROPERTY(QString startupTheme READ startupTheme WRITE setStartupTheme)
    Q_PROPERTY(QStringList themeDirs READ themeDirs WRITE setThemeDirs)
    Q_PROPERTY(bool generateThemeTemplateEnable READ isGenerateThemeTemplateEnable WRITE setGenerateThemeTemplateEnable)
    Q_PROPERTY(int mouseAreaCursorShape READ mouseAreaCursorShape WRITE setMouseAreaCursorShape)

public:
    explicit QEXTQuickWorld(QQuickItem *parent = QEXT_DECL_NULLPTR);
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

protected:
    QScopedPointer<QEXTQuickWorldPrivate> dd_ptr;
};



#endif // _QEXTQUICKWORLD_H
