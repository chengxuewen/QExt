// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "view/widgets/collapsiblelistwidget.h"
#include "view/widgets/collapsiblebar.h"
#include <QSplitter>
#include <QVBoxLayout>

using namespace ModelView;

QExtMvvmCollapsibleListWidget::QExtMvvmCollapsibleListWidget(QWidget* parent)
    : QWidget(parent), m_splitter(new QSplitter)
{
    m_splitter->setOrientation(Qt::Vertical);

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_splitter);
}

void QExtMvvmCollapsibleListWidget::addWidget(QWidget* widget, const QString& title, bool collapsed)
{
    // add bar which will be uncollapsible and will control the appearance of our widget
    auto bar = new QExtMvvmCollapsibleBar(m_splitter);
    m_splitter->addWidget(bar);

    // add widget itself
    m_splitter->addWidget(widget);

    // setup bar for widget
    bar->setWidget(widget, title);
    m_splitter->setCollapsible(m_splitter->indexOf(bar), false);

    if (collapsed)
        widget->setVisible(false);
}
