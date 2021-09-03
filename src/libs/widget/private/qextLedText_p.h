#ifndef QEXTLEDTEXT_P_H
#define QEXTLEDTEXT_P_H

#include <qextWidgetGlobal.h>
#include <qextLedText.h>

#include <qextobject_p.h>

#include <QTimer>
#include <QColor>
#include <QSizeF>
#include <QPointF>

class QEXTLedText;
class QEXT_WIDGET_API QEXTLedTextPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTLedTextPrivate(QEXTLedText *qq);
    ~QEXTLedTextPrivate();

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
    QEXTLedText::Animation m_animationType;
    QScopedPointer<QTimer> m_animationTimer;
    int m_animationInterval;
    int m_animationOffset;

private:
    QEXT_DECL_PUBLIC(QEXTLedText)
    QEXT_DISABLE_COPY_MOVE(QEXTLedTextPrivate)
};


#endif // QEXTLEDTEXT_P_H
