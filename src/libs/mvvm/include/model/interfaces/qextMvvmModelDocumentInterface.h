#ifndef _QEXTMVVMMODELDOCUMENTINTERFACE_H
#define _QEXTMVVMMODELDOCUMENTINTERFACE_H

#include <qextMvvmGlobal.h>
#include <string>

namespace ModelView
{

//! Pure virtual interface to save and restore session models to/from disk.

class QEXT_MVVM_API QEXTMvvmModelDocumentInterface
{
public:
    virtual ~QEXTMvvmModelDocumentInterface() = default;

    virtual void save(const std::string& file_name) const = 0;
    virtual void load(const std::string& file_name) = 0;
};

} // namespace ModelView

#endif // _QEXTMVVMMODELDOCUMENTINTERFACE_H
