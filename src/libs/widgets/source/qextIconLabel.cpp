#include <private/qextIconLabel_p.h>


QEXTIconLabelPrivate::QEXTIconLabelPrivate(QEXTIconLabel *q)
    : q_ptr(q)
{

}

QEXTIconLabelPrivate::~QEXTIconLabelPrivate()
{

}

QEXTIconLabel::QEXTIconLabel(QWidget *parent)
    : QWidget(parent), dd_ptr(new QEXTIconLabelPrivate(this))
{

}

QEXTIconLabel::~QEXTIconLabel()
{

}

void QEXTIconLabel::paintEvent(QPaintEvent *)
{

}
