#ifndef QEXTLABELGADGET_P_H
#define QEXTLABELGADGET_P_H

#include <qextquickglobal.h>

#include <qextobject_p.h>

#include <QColor>
#include <QFont>



class QEXTTextGadget;
class QEXT_QUICK_API QEXTTextGadgetPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTTextGadgetPrivate(QEXTTextGadget *qq);
    ~QEXTTextGadgetPrivate();

    QString m_text;
    QColor m_color;
    qreal m_scale;
    QFont m_font;
    int m_fontSize;

private:
    QEXT_DECLARE_PUBLIC(QEXTTextGadget)
    QEXT_DISABLE_COPY_MOVE(QEXTTextGadgetPrivate)
};



#endif // QEXTLABELGADGET_P_H
