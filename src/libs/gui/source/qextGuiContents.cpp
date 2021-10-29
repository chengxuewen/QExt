#include <qextGuiContents.h>
#include <qextGuiContents_p.h>

#include <QRectF>

QEXTGuiContentsPrivate::QEXTGuiContentsPrivate(QEXTGuiContents *q)
    : q_ptr(q)
    , m_item(QEXT_DECL_NULLPTR)
    , m_x(0)
    , m_y(0)
    , m_width(0)
    , m_height(0)
{

}

QEXTGuiContentsPrivate::~QEXTGuiContentsPrivate()
{

}



QEXTGuiContents::QEXTGuiContents(QEXTGuiGVItem *item)
    : d_ptr(new QEXTGuiContentsPrivate(this))
{
    d_ptr->m_item = item;
}

QEXTGuiContents::~QEXTGuiContents()
{

}

QRectF QEXTGuiContents::rectF() const
{

}

void QEXTGuiContents::childRemoved(QEXTGuiGVItem *item)
{

}

void QEXTGuiContents::childAdded(QEXTGuiGVItem *item)
{

}

void QEXTGuiContents::calcGeometry()
{
    this->calcWidth();
    this->calcHeight();
}

void QEXTGuiContents::complete()
{

}

void QEXTGuiContents::itemVisibilityChanged(QEXTGuiGVItem *item)
{

}

void QEXTGuiContents::itemGeometryChanged(QEXTGuiGVItem *item, const QRectF &newGeometry, const QRectF &oldGeometry)
{

}

void QEXTGuiContents::itemDestroyed(QEXTGuiGVItem *item)
{

}

void QEXTGuiContents::calcHeight(QEXTGuiGVItem *changed)
{

}

void QEXTGuiContents::calcWidth(QEXTGuiGVItem *changed)
{

}
