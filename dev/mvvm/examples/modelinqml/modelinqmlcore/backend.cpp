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

using namespace ModelView;

struct BackEnd::BackEndImpl {
    QExtUniquePointer<ParticleModel> m_model;
    QExtUniquePointer<ParticleViewModel> m_viewModel;
    TableModel* m_tableModel{nullptr};

    BackEndImpl()
        : m_model(qextMakeUnique<ParticleModel>())
        , m_viewModel(qextMakeUnique<ParticleViewModel>(m_model.get()))
        , m_tableModel(new TableModel)
    {
        m_viewModel->setRootSessionItem(m_model->topItem());
    }
};

BackEnd::BackEnd(QObject* parent) : QObject(parent), p_impl(qextMakeUnique<BackEndImpl>()) {}

BackEnd::~BackEnd() = default;

TableModel* BackEnd::tableModel() const
{
    return p_impl->m_tableModel;
}

ParticleViewModel* BackEnd::particleViewModel() const
{
    return p_impl->m_viewModel.get();
}
