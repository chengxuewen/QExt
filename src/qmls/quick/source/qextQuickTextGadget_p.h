#ifndef _QEXTQUICKLABELGADGET_P_H
#define _QEXTQUICKLABELGADGET_P_H

#include <qextQuickTextGadget.h>

#include <QColor>
#include <QFont>

class QEXT_QUICK_API QExtQuickTextGadgetPrivate
{
    Q_DISABLE_COPY(QExtQuickTextGadgetPrivate)
    Q_DECLARE_PUBLIC(QExtQuickTextGadget)
public:
    explicit QExtQuickTextGadgetPrivate(QExtQuickTextGadget *q);
    virtual ~QExtQuickTextGadgetPrivate();

    QExtQuickTextGadget * const q_ptr;

    QString m_text;
    QColor m_color;
    qreal m_scale;
    QFont m_font;
    int m_fontSize;

private:
};

#endif // _QEXTQUICKLABELGADGET_P_H
