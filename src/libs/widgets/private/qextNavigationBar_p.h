#ifndef _QEXTNAVIGATIONBAR_P_H
#define _QEXTNAVIGATIONBAR_P_H

#include <qextWidgetGlobal.h>
#include <qextNavigationBar.h>

class QEXTNavigationBar;
class QEXT_WIDGETS_API QEXTNavigationBarPrivate
{
    Q_DISABLE_COPY(QEXTNavigationBarPrivate)
    Q_DECLARE_PUBLIC(QEXTNavigationBar)
public:
    explicit QEXTNavigationBarPrivate(QEXTNavigationBar *q);
    virtual ~QEXTNavigationBarPrivate();

    int initStep(int distance);

    QEXTNavigationBar * const q_ptr;

    QColor m_backgroundStartColor;
    QColor m_backgroundEndColor;

    QColor m_barStartColor;
    QColor m_barEndColor;

    QColor m_textNormalColor;
    QColor m_textSelectColor;

    QColor m_oldBackgroundEndColor;
    QColor m_oldBarEndColor;

    QString m_items;
    int m_currentIndex;
    QString m_currentItem;

    int m_backgroundRadius;
    int m_barRadius;
    int m_space;

    int m_lineWidth;
    QColor m_lineColor;

    QEXTNavigationBar::BarStyleType m_barStyle;

    bool m_keyMoveEnable;
    bool m_horizontal;
    bool m_flat;

    QVector<QPair<QString, QRectF> > m_listItem;

    QRectF m_barRect;
    QRectF m_targetRect;
    double m_barLen;
    double m_targetLen;

    double m_initLen;
    int m_step;

    bool m_isForward;
    bool m_isVirgin;
    QTimer *m_timer;
};

#endif // _QEXTNAVIGATIONBAR_P_H
