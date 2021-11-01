// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "qcustomplot.h"
#include <qextMvvmComboProperty.h>
#include <plotting/pencontroller.h>
#include <qextMvvmPlotTableItems.h>
#include <stdexcept>

using namespace ModelView;

namespace
{
//! Returns Qt pen style from current QEXTMvvmComboProperty index.
Qt::PenStyle getQtPenFromComboIndex(const QEXTMvvmComboProperty& combo)
{
    // our QEXTMvvmComboProperty for pens coincide with Qt definition
    return static_cast<Qt::PenStyle>(combo.currentIndex());
}
} // namespace

struct PenController::PenControllerImpl {
    QCPGraph* m_graph{nullptr};
    PenControllerImpl(QCPGraph* graph) : m_graph(graph)
    {
        if (!m_graph)
            throw std::runtime_error("Error in PenController: uninitialised graph.");
    }

    void update_graph_from_item(QEXTMvvmPenItem* item)
    {
        QColor color(QString::fromStdString(item->colorName()));
        auto pencombo = item->property<QEXTMvvmComboProperty>(QEXTMvvmPenItem::P_STYLE);
        auto penwidth = item->property<int>(QEXTMvvmPenItem::P_WIDTH);

        QPen pen;
        pen.setColor(color);
        pen.setStyle(getQtPenFromComboIndex(pencombo));
        pen.setWidth(penwidth);
        m_graph->setPen(pen);

        m_graph->parentPlot()->replot();
    }
};

PenController::PenController(QCPGraph* graph) : p_impl(std::make_unique<PenControllerImpl>(graph))
{
}

PenController::~PenController() = default;

void PenController::subscribe()
{
    auto on_property_change = [this](auto, auto) { p_impl->update_graph_from_item(currentItem()); };
    setOnPropertyChange(on_property_change);

    p_impl->update_graph_from_item(currentItem());
}
