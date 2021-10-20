#include <qextGuiGVView.h>
#include <qextGuiGVView_p.h>

QEXTGuiGVViewPrivate::QEXTGuiGVViewPrivate(QEXTGuiGVView *q)
    : q_ptr(q)
{

}

QEXTGuiGVViewPrivate::~QEXTGuiGVViewPrivate()
{

}



QEXTGuiGVView::QEXTGuiGVView(QWidget *parent)
    : QGraphicsView(parent), d_ptr(new QEXTGuiGVViewPrivate(this))
{

}

QEXTGuiGVView::~QEXTGuiGVView()
{

}
