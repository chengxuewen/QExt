#ifndef _QEXTICONLABEL_H
#define _QEXTICONLABEL_H

#include <qextWidgetGlobal.h>

#include <QWidget>

class QEXTIconLabelPrivate;
class QEXT_WIDGETS_API QEXTIconLabel : public QWidget
{
    Q_OBJECT

public:
    explicit QEXTIconLabel(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTIconLabel();

protected:
    void paintEvent(QPaintEvent *) QEXT_DECL_OVERRIDE;

    QScopedPointer<QEXTIconLabelPrivate> dd_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTIconLabel)
    QEXT_DECL_PRIVATE_D(dd_ptr, QEXTIconLabel)
};

#endif // _QEXTICONLABEL_H
