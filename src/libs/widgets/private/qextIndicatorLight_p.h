#ifndef _QEXTINDICATORLIGHT_P_H
#define _QEXTINDICATORLIGHT_P_H

#include <qextWidgetGlobal.h>
#include <qextIndicatorLight.h>

#include <QColor>
#include <QTimer>

class QEXTIndicatorLight;
class QEXT_WIDGETS_API QEXTIndicatorLightPrivate
{
    Q_DECLARE_PUBLIC(QEXTIndicatorLight)
    Q_DISABLE_COPY(QEXTIndicatorLightPrivate)
public:
    explicit QEXTIndicatorLightPrivate(QEXTIndicatorLight *q);
    virtual ~QEXTIndicatorLightPrivate();

    QEXTIndicatorLight * const q_ptr;

    QString m_text;
    QColor m_lightTextColor;
    QColor m_normalTextColor;
    QColor m_lightBackgroundColor;
    QColor m_normalBackgroundColor;
    int m_fontPixelSize;

    QColor m_outBorderStartColor;
    QColor m_outBorderEndColor;
    QColor m_inBorderStartColor;
    QColor m_inBorderEndColor;
    QEXTIndicatorLight::Style m_style;
    QEXTIndicatorLight::Shape m_shape;

    bool m_moveEnable;
    bool m_overlayVisiable;
    QColor m_overlayColor;

    QScopedPointer<QTimer> m_flickerTimer;
    bool m_lightState;
};

#endif // _QEXTINDICATORLIGHT_P_H
