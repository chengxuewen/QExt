// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MODELINQMLCORE_PARTICLEVIEWMODEL_H
#define MODELINQMLCORE_PARTICLEVIEWMODEL_H

#include <viewmodel/qextMvvmPropertyViewModel.h>

class ParticleModel;

class ParticleViewModel : public ModelView::QEXTMvvmPropertyViewModel
{
    Q_OBJECT

public:
    ParticleViewModel(ParticleModel* model = nullptr);
};

#endif // MODELINQMLCORE_PARTICLEVIEWMODEL_H
