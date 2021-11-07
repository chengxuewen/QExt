// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "backend.h"
#include "particlemodel.h"
#include "particleviewmodel.h"
#include "tablemodel.h"
#include <qextMvvmViewModelFactory.h>
#include <qextMvvmViewModel.h>



struct BackEnd::BackEndImpl {
    QScopedPointer<ParticleModel> m_model;
    QScopedPointer<ParticleViewModel> m_viewModel;
    TableModel* m_tableModel{nullptr};

    BackEndImpl()
        : m_model(new ParticleModel),
          m_viewModel(new ParticleViewModel(m_model.get())),
          m_tableModel(new TableModel)
    {
        m_viewModel->setRootItem(m_model->topItem());
    }
};

BackEnd::BackEnd(QObject* parent) : QObject(parent), p_impl(new BackEndImpl) {}

BackEnd::~BackEnd() = default;

TableModel* BackEnd::tableModel() const
{
    return p_impl->m_tableModel;
}

ParticleViewModel* BackEnd::particleViewModel() const
{
    return p_impl->m_viewModel.get();
}
