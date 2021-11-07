#ifndef _QEXTMVVMMODELDOCUMENTINTERFACE_H
#define _QEXTMVVMMODELDOCUMENTINTERFACE_H

#include <qextMvvmGlobal.h>

#include <QString>

//! Pure virtual interface to save and restore session models to/from disk.

class QEXT_MVVM_API QEXTMvvmModelDocumentInterface
{
public:
    virtual ~QEXTMvvmModelDocumentInterface() { }

    virtual void save(const QString &fileName) const = 0;
    virtual void load(const QString &fileName) = 0;
};


#endif // _QEXTMVVMMODELDOCUMENTINTERFACE_H
