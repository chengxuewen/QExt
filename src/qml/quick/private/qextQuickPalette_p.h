#ifndef _QEXTCOLOR_P_H
#define _QEXTCOLOR_P_H

#include <qextQuickGlobal.h>

class QEXTQuickPalette;
class QEXT_QUICK_API QEXTQuickPalettePrivate
{
    Q_DISABLE_COPY(QEXTQuickPalettePrivate)
    Q_DECLARE_PUBLIC(QEXTQuickPalette)
public:
    explicit QEXTQuickPalettePrivate(QEXTQuickPalette *q);
    virtual ~QEXTQuickPalettePrivate();

    QEXTQuickPalette * const q_ptr;

    QVector<QVector<QColor>> m_materialColorVector;
    QVector<QColor> m_brandColorVector;
    QVector<QColor> m_textColorVector;
    QVector<QColor> m_borderColorVector;
};

#endif // _QEXTCOLOR_P_H
