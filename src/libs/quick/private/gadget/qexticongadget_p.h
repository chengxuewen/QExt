#ifndef QEXTICONGADGET_P_H
#define QEXTICONGADGET_P_H

#include <qextquickglobal.h>

#include <qextobject_p.h>

#include <QColor>

class QEXTIconGadget;
class QEXT_QUICK_API QEXTIconGadgetPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTIconGadgetPrivate(QEXTIconGadget *qq);
    ~QEXTIconGadgetPrivate();

    qreal m_width;
    qreal m_height;
    int m_type;
    int m_position;
    qreal m_scale;
    QColor m_color;
    QString m_source;

private:
    QEXT_DECLARE_PUBLIC(QEXTIconGadget)
    QEXT_DISABLE_COPY_MOVE(QEXTIconGadgetPrivate)
};

#endif // QEXTICONGADGET_P_H
