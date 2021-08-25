#include <qextIconLabel.h>
#include <qextIconLabel_p.h>


QEXTIconLabelPrivate::QEXTIconLabelPrivate(QEXTIconLabel *qq)
    : QEXTObjectPrivate(qq)
{

}

QEXTIconLabelPrivate::~QEXTIconLabelPrivate()
{

}

QEXTIconLabel::QEXTIconLabel(QWidget *parent)
    : QWidget(parent), QEXTObject(*(new QEXTIconLabelPrivate(this)))
{

}

QEXTIconLabel::~QEXTIconLabel()
{

}

void QEXTIconLabel::paintEvent(QPaintEvent *)
{

}
