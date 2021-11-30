#ifndef _QEXTICONBUTTON_P_H
#define _QEXTICONBUTTON_P_H

#include <QtGlobal>

class QColor;

//class QtMaterialRippleOverlay;

class QEXTIconButton;
class QEXTIconButtonPrivate
{
    Q_DISABLE_COPY(QEXTIconButtonPrivate)
    Q_DECLARE_PUBLIC(QEXTIconButton)
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
};

#endif // _QEXTICONBUTTON_P_H
