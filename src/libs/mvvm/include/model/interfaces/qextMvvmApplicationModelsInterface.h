#ifndef _QEXTMVVMAPPLICATIONMODELSINTERFACE_H
#define _QEXTMVVMAPPLICATIONMODELSINTERFACE_H

#include <qextMvvmGlobal.h>
#include <QVector>


class QEXTMvvmModel;

//! Interface to access application's model list for further manipulation.
//! Used in the context of save/load projects.

class QEXT_MVVM_API QEXTMvvmApplicationModelsInterface
{
public:
    //! Returns vector of models intended for saving on disk.
    virtual QVector<QEXTMvvmModel *> persistentModels() const = 0;
};


#endif //  _QEXTMVVMAPPLICATIONMODELSINTERFACE_H
