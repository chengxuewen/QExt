#ifndef _QEXTNAVIGATIONBUTTON_P_H
#define _QEXTNAVIGATIONBUTTON_P_H

#include <qextWidgetGlobal.h>
#include <qextNavigationButton.h>

class QEXTNavigationButton;
class QEXT_WIDGETS_API QEXTNavigationButtonPrivate
{
public:
    explicit QEXTNavigationButtonPrivate(QEXTNavigationButton *q);
    virtual ~QEXTNavigationButtonPrivate();

    QEXTNavigationButton * const q_ptr;

    int m_leftPadding;
    int m_rightPadding;
    int m_topPadding;
    int m_bottomPadding;
    QEXTNavigationButton::TextAlignType m_textAlign;

    bool m_triangleVisiable;
    QEXTNavigationButton::PositionType m_trianglePosition;
    int m_triangleLen;
    QColor m_triangleColor;

    bool m_iconVisiable;
    QEXTNavigationButton::PositionType m_iconPosition;
    int m_iconSpace;
    QSize m_iconSize;
    QPixmap m_normalIcon;
    QPixmap m_hoverIcon;
    QPixmap m_checkIcon;
    QChar m_normalFontIcon;
    QChar m_hoverFontIcon;
    QChar m_checkFontIcon;

    bool m_lineVisiable;
    QEXTNavigationButton::PositionType m_linePosition;
    int m_lineSpace;
    int m_lineWidth;
    QColor m_lineColor;

    QColor m_normalBackgroundColor;
    QColor m_hoverBackgroundColor;
    QColor m_checkBackgroundColor;
    QColor m_normalTextColor;
    QColor m_hoverTextColor;
    QColor m_checkTextColor;

    QBrush m_normalBackgroundBrush;
    QBrush m_hoverBackgroundBrush;
    QBrush m_checkBackgroundBrush;

    bool m_hovered;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTNavigationButtonPrivate)
    QEXT_DECL_PUBLIC(QEXTNavigationButton)
};

#endif // _QEXTNAVIGATIONBUTTON_P_H
