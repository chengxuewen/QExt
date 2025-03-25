// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmAdjustingScrollArea.h>
#include <QEvent>
#include <QScrollBar>

using namespace ModelView;

QExtMvvmAdjustingScrollArea::QExtMvvmAdjustingScrollArea(QWidget* parent) : QScrollArea(parent)
{
    setObjectName("QExtMvvmAdjustingScrollArea");
    setContentsMargins(0, 0, 0, 0);
    setWidgetResizable(true);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setStyleSheet("QScrollArea#QExtMvvmAdjustingScrollArea {border: 0px; background-color:transparent;}");
}

void QExtMvvmAdjustingScrollArea::setWidget(QWidget* w)
{
    QScrollArea::setWidget(w);
    w->installEventFilter(this);
}

QSize QExtMvvmAdjustingScrollArea::sizeHint() const
{
    auto horizontal = horizontalScrollBar();
    QSize result(viewport()->width(), widget()->height() + horizontal->height() * 2);
    return result;
}

bool QExtMvvmAdjustingScrollArea::eventFilter(QObject* obj, QEvent* ev)
{
    if (obj == widget() && ev->type() != QEvent::Resize) {
        widget()->setMaximumWidth(viewport()->width());
        setMaximumHeight(height() - viewport()->height() + widget()->height());
    }

    return QScrollArea::eventFilter(obj, ev);
}
