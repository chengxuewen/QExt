#ifndef _QEXTMVVMCOREMODELDOCUMENTINTERFACE_H
#define _QEXTMVVMCOREMODELDOCUMENTINTERFACE_H

#include <qextMvvmGlobal.h>

#include <string>

namespace ModelView
{

//! Pure virtual interface to save and restore session models to/from disk.

class QEXT_MVVM_API QEXTMVVMModelDocumentInterface
{
public:
    virtual ~QEXTMVVMModelDocumentInterface() = default;

    virtual void save(const std::string& file_name) const = 0;
    virtual void load(const std::string& file_name) = 0;
};

} // namespace ModelView

#endif // _QEXTMVVMCOREMODELDOCUMENTINTERFACE_H
