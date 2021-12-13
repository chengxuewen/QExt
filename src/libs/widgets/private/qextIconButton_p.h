#ifndef _QEXTICONBUTTON_P_H
#define _QEXTICONBUTTON_P_H

#include <qextWidgetGlobal.h>

class QColor;

//class QtMaterialRippleOverlay;

class QEXTIconButton;
class QEXT_WIDGETS_API QEXTIconButtonPrivate
{
public:
    explicit QEXTIconButtonPrivate(QEXTIconButton *q);
    virtual ~QEXTIconButtonPrivate();

    void init();
    void updateRipple();

    QEXTIconButton * const q_ptr;
//    QtMaterialRippleOverlay *rippleOverlay;
    QColor m_iconColor;
    QColor m_backgroundColor;
    QColor m_disabledColor;
    bool m_useThemeColors;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTIconButtonPrivate)
    QEXT_DECL_PUBLIC(QEXTIconButton)
};

#endif // _QEXTICONBUTTON_P_H
