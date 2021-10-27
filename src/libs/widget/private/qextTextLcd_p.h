#ifndef _QEXTTEXTLCD_P_H
#define _QEXTTEXTLCD_P_H

#include <qextWidgetGlobal.h>
#include <qextTextLcd.h>

#include <QTimer>
#include <QColor>
#include <QSizeF>
#include <QPointF>

class QEXTTextLcd;
class QEXT_WIDGET_API QEXTTextLcdPrivate
{
public:
    explicit QEXTTextLcdPrivate(QEXTTextLcd *q);
    virtual ~QEXTTextLcdPrivate();

    QEXTTextLcd * const q_ptr;

    QSizeF m_ledTextSizeF;
    QSize m_imageSize;
    QString m_text;                  //文字

    int m_textAlignment;
    int m_fontPixelSize;
    int m_rowCount;
    int m_columnCount;
    double m_spaceFactory;
    double m_space;
    double m_radius;
    double m_step;
    double m_hBorder;
    QVector<QVector<QPointF> > m_pointFVector;

    QColor m_foregroundColor;           //前景色
    QColor m_backgroundColor;           //背景色
    QColor m_textColor;

    bool m_highLightBorder;
    QEXTTextLcd::Animation m_animationType;
    QScopedPointer<QTimer> m_animationTimer;
    int m_animationInterval;
    int m_animationOffset;

private:
    QEXT_DECL_PUBLIC(QEXTTextLcd)
    QEXT_DISABLE_COPY_MOVE(QEXTTextLcdPrivate)
};


#endif // _QEXTTEXTLCD_P_H
