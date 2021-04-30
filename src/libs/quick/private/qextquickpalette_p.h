#ifndef QEXTCOLOR_P_H
#define QEXTCOLOR_P_H

#include <qextquickglobal.h>

#include <qextobject_p.h>

class QEXTQuickPalette;
class QEXT_QUICK_API QEXTQuickPalettePrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTQuickPalettePrivate(QEXTQuickPalette *qq);
    ~QEXTQuickPalettePrivate();

    QVector<QVector<QColor>> m_materialColorVector;
    QVector<QColor> m_brandColorVector;
    QVector<QColor> m_textColorVector;
    QVector<QColor> m_borderColorVector;

private:
    QEXT_DECLARE_PUBLIC(QEXTQuickPalette)
    QEXT_DISABLE_COPY_MOVE(QEXTQuickPalettePrivate)
};

#endif // QEXTCOLOR_P_H
