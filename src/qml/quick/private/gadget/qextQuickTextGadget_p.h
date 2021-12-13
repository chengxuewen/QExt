#ifndef _QEXTLABELGADGET_P_H
#define _QEXTLABELGADGET_P_H

#include <qextQuickGlobal.h>

#include <QColor>
#include <QFont>

class QEXTQuickTextGadget;
class QEXT_QUICK_API QEXTQuickTextGadgetPrivate
{
    Q_DISABLE_COPY(QEXTQuickTextGadgetPrivate)
    Q_DECLARE_PUBLIC(QEXTQuickTextGadget)
public:
    explicit QEXTQuickTextGadgetPrivate(QEXTQuickTextGadget *q);
    virtual ~QEXTQuickTextGadgetPrivate();

    QEXTQuickTextGadget * const q_ptr;

    QString m_text;
    QColor m_color;
    qreal m_scale;
    QFont m_font;
    int m_fontSize;

private:
};



#endif // _QEXTLABELGADGET_P_H
