#ifndef _QEXTQUICKPALETTE_P_H
#define _QEXTQUICKPALETTE_P_H

#include <qextQuickPalette.h>

class QEXT_QUICK_API QExtQuickPalettePrivate
{
    Q_DISABLE_COPY(QExtQuickPalettePrivate)
    Q_DECLARE_PUBLIC(QExtQuickPalette)
public:
    explicit QExtQuickPalettePrivate(QExtQuickPalette *q);
    virtual ~QExtQuickPalettePrivate();

    QExtQuickPalette * const q_ptr;

    QVector<QVector<QColor>> m_materialColorVector;
    QVector<QColor> m_brandColorVector;
    QVector<QColor> m_textColorVector;
    QVector<QColor> m_borderColorVector;
};

#endif // _QEXTQUICKPALETTE_P_H
