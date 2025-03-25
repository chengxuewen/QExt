// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmPenController.h>
#include <qextMvvmComboProperty.h>
#include <qextMvvmPlotTableItems.h>
#include <qcustomplot.h>
#include <stdexcept>

using namespace ModelView;

namespace {
//! Returns Qt pen style from current QExtMvvmComboProperty index.
Qt::PenStyle getQtPenFromComboIndex(const QExtMvvmComboProperty& combo)
{
    // our QExtMvvmComboProperty for pens coincide with Qt definition
    return static_cast<Qt::PenStyle>(combo.currentIndex());
}
} // namespace

struct QExtMvvmPenController::PenControllerImpl {
    QCPGraph* m_graph{nullptr};
    PenControllerImpl(QCPGraph* graph) : m_graph(graph)
    {
        if (!m_graph)
            throw std::runtime_error("Error in QExtMvvmPenController: uninitialised graph.");
    }

    void update_graph_from_item(QExtMvvmPenItem* item)
    {
        QColor color(QString::fromStdString(item->colorName()));
        auto pencombo = item->property<QExtMvvmComboProperty>(QExtMvvmPenItem::P_STYLE);
        auto penwidth = item->property<int>(QExtMvvmPenItem::P_WIDTH);

        QPen pen;
        pen.setColor(color);
        pen.setStyle(getQtPenFromComboIndex(pencombo));
        pen.setWidth(penwidth);
        m_graph->setPen(pen);

        m_graph->parentPlot()->replot();
    }
};

QExtMvvmPenController::QExtMvvmPenController(QCPGraph* graph) : p_impl(qextMakeUnique<PenControllerImpl>(graph))
{
}

QExtMvvmPenController::~QExtMvvmPenController() = default;

void QExtMvvmPenController::subscribe()
{
    auto on_property_change = [this](QExtMvvmSessionItem*, std::string) { p_impl->update_graph_from_item(currentItem()); };
    setOnPropertyChange(on_property_change);

    p_impl->update_graph_from_item(currentItem());
}
