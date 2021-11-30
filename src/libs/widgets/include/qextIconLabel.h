#ifndef _QEXTICONLABEL_H
#define _QEXTICONLABEL_H

#include <qextWidgetGlobal.h>

#include <QWidget>

class QEXTIconLabelPrivate;
class QEXT_WIDGETS_API QEXTIconLabel : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(QEXTIconLabel)
    Q_DECLARE_PRIVATE_D(dd_ptr, QEXTIconLabel)

public:
    explicit QEXTIconLabel(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTIconLabel();

protected:
    void paintEvent(QPaintEvent *) QEXT_DECL_OVERRIDE;

    QScopedPointer<QEXTIconLabelPrivate> dd_ptr;
};

#endif // _QEXTICONLABEL_H
