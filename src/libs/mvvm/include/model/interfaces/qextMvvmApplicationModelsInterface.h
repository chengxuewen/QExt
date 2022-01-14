#ifndef _QEXTMVVMINTERFACESAPPLICATIONMODELSINTERFACE_H
#define _QEXTMVVMINTERFACESAPPLICATIONMODELSINTERFACE_H

#include <qextMvvmGlobal.h>

#include <vector>

namespace ModelView
{

class QEXTMvvmSessionModel;

//! Interface to access application's model list for further manipulation.
//! Used in the context of save/load projects.

class QEXT_MVVM_API QEXTMvvmApplicationModelsInterface
{
public:
    //! Returns vector of models intended for saving on disk.
    virtual std::vector<QEXTMvvmSessionModel*> persistent_models() const = 0;
};

} // namespace ModelView

#endif //  _QEXTMVVMINTERFACESAPPLICATIONMODELSINTERFACE_H
