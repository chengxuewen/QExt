#ifndef QEXTTHEMEHELPER_H
#define QEXTTHEMEHELPER_H

#include <qextThemeGlobal.h>
#include <qextObject.h>

#include <QObject>

class QEXTThemeHelperPrivate;
class QEXT_THEME_API QEXTThemeHelper : public QObject, public QEXTObject
{
    Q_OBJECT
public:
    enum ColorType {
        Color_Unknown,
        Color_Light,
        Color_Dark
    };

    enum SingleScope {
        UserScope,
        GroupScope,
        WorldScope
    };

    typedef QEXTThemeHelper *(*HelperCreator)();
    static void registerInstanceCreator(HelperCreator creator);
    static QEXTThemeHelper *instance();
    ~QEXTThemeHelper();

    ColorType themeType() const;
    ColorType paletteType() const;

protected:
    QEXTThemeHelper(QObject *parent = QEXT_DECL_NULLPTR);

    virtual void initialize();

private:
    friend class QEXTThemeHelperWraper;
    QEXT_DECL_PRIVATE(QEXTThemeHelper)
    QEXT_DISABLE_COPY_MOVE(QEXTThemeHelper)
};

#endif // QEXTTHEMEHELPER_H
