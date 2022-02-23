#ifndef _QEXTQMLQUICKLABELGADGET_P_H
#define _QEXTQMLQUICKLABELGADGET_P_H

#include <qextQmlQuickGlobal.h>

#include <QColor>
#include <QFont>

class QEXTQmlQuickTextGadget;
class QEXT_QUICK_API QEXTQmlQuickTextGadgetPrivate
{
    Q_DISABLE_COPY(QEXTQmlQuickTextGadgetPrivate)
    Q_DECLARE_PUBLIC(QEXTQmlQuickTextGadget)
public:
    explicit QEXTQmlQuickTextGadgetPrivate(QEXTQmlQuickTextGadget *q);
    virtual ~QEXTQmlQuickTextGadgetPrivate();

    QEXTQmlQuickTextGadget * const q_ptr;

    QString m_text;
    QColor m_color;
    qreal m_scale;
    QFont m_font;
    int m_fontSize;

private:
};

#endif // _QEXTQMLQUICKLABELGADGET_P_H
