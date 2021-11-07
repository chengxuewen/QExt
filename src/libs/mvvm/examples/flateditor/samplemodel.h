// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef SAMPLEMODEL_H
#define SAMPLEMODEL_H

#include <qextMvvmModel.h>

//! Main application model.

class SampleModel : public QEXTMvvmModel
{
public:
    SampleModel();

private:
    void init_model();
};

#endif
