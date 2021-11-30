#ifndef _QEXTSWITCHBUTTON_P_H
#define _QEXTSWITCHBUTTON_P_H

#include <qextWidgetGlobal.h>
#include <qextSwitchButton.h>

#include <QVariantAnimation>

class QEXTSwitchButton;
class QEXT_WIDGETS_API QEXTSwitchButtonPrivate
{
    Q_DECLARE_PUBLIC(QEXTSwitchButton)
    Q_DISABLE_COPY(QEXTSwitchButtonPrivate)
public:
    explicit QEXTSwitchButtonPrivate(QEXTSwitchButton *q);
    virtual ~QEXTSwitchButtonPrivate();

    QEXTSwitchButton * const q_ptr;

    int m_space;
    int m_rectRadius;
    bool m_checked;
    bool m_textVisiable;
    bool m_circleVisiable;
    bool m_animationEnable;

    QEXTSwitchButton::Style m_buttonStyle;

    QColor m_backgroundOffColor;
    QColor m_backgroundOnColor;
    QColor m_sliderOffColor;
    QColor m_sliderOnColor;
    QColor m_offTextColor;
    QColor m_onTextColor;

    QString m_offText;
    QString m_onText;

    int m_step;
    int m_startX;
    int m_endX;
    QScopedPointer<QTimer> m_timer;
};

#endif // _QEXTSWITCHBUTTON_P_H
