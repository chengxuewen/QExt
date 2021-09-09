#ifndef QEXTTHEMEHELPER_P_H
#define QEXTTHEMEHELPER_P_H

#include <qextThemeGlobal.h>
#include <qextThemeHelper.h>

#include <qextObject_p.h>

class QEXTThemeHelper;
class QEXT_THEME_API QEXTThemeHelperPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTThemeHelperPrivate(QEXTThemeHelper *qq);
    ~QEXTThemeHelperPrivate();

    QEXTThemeHelper::ColorType m_themeType;
    QEXTThemeHelper::ColorType m_paletteType;

private:
    QEXT_DECL_PUBLIC(QEXTThemeHelper)
    QEXT_DISABLE_COPY_MOVE(QEXTThemeHelperPrivate)
};

#endif // QEXTTHEMEHELPER_P_H
