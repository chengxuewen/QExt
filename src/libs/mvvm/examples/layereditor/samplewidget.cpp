// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QTreeView>
#include <QVBoxLayout>
#include "applicationmodels.h"
#include "materialmodel.h"
#include "materialtablewidget.h"
#include "multilayertreeview.h"
#include "samplemodel.h"
#include "samplewidget.h"
#include <qextMvvmViewModelFactory.h>
#include <qextMvvmItemsTreeView.h>



SampleWidget::SampleWidget(ApplicationModels* models, QWidget* parent)
    : QWidget(parent)
    , m_materialTree(new QEXTMvvmItemsTreeView)
    , m_sampleTree(new QEXTMvvmItemsTreeView)
    , m_materialTableWidget(new MaterialTableWidget(models->materialModel()))
    , m_multiLayerTreeView(new MultiLayerTreeView(models))
    , m_models(models)
{
    auto mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);

    mainLayout->addLayout(create_top_layout());
    mainLayout->addLayout(create_bottom_layout());

    setLayout(mainLayout);
}

QBoxLayout* SampleWidget::create_top_layout()
{
    auto result = new QHBoxLayout;

    m_materialTree->setViewModel(QEXTMvvmViewModelFactory::createDefaultViewModel(m_models->materialModel()));
    m_sampleTree->setViewModel(QEXTMvvmViewModelFactory::createDefaultViewModel(m_models->sampleModel()));

    result->addWidget(m_materialTree);
    result->addWidget(m_sampleTree);
    return result;
}

QBoxLayout* SampleWidget::create_bottom_layout()
{
    auto result = new QHBoxLayout;
    result->addWidget(m_materialTableWidget);
    result->addWidget(m_multiLayerTreeView);
    return result;
}
