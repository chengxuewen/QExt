#ifndef _QEXTQMLQUICKPALETTE_P_H
#define _QEXTQMLQUICKPALETTE_P_H

#include <qextQmlQuickGlobal.h>

class QEXTQmlQuickPalette;
class QEXT_QUICK_API QEXTQmlQuickPalettePrivate
{
    Q_DISABLE_COPY(QEXTQmlQuickPalettePrivate)
    Q_DECLARE_PUBLIC(QEXTQmlQuickPalette)
public:
    explicit QEXTQmlQuickPalettePrivate(QEXTQmlQuickPalette *q);
    virtual ~QEXTQmlQuickPalettePrivate();

    QEXTQmlQuickPalette * const q_ptr;

    QVector<QVector<QColor>> m_materialColorVector;
    QVector<QColor> m_brandColorVector;
    QVector<QColor> m_textColorVector;
    QVector<QColor> m_borderColorVector;
};

#endif // _QEXTQMLQUICKPALETTE_P_H
