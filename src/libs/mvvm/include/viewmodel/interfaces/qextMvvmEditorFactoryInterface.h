#ifndef _QEXTMVVMEDITORSEDITORFACTORYINTERFACE_H
#define _QEXTMVVMEDITORSEDITORFACTORYINTERFACE_H

#include <qextMvvmGlobal.h>

#include <memory>
#include <string>

class QModelIndex;
class QWidget;

namespace ModelView
{

class QEXTMvvmCustomEditor;

//! Interface for custom editor factory.
//! Intended for editor construction in cells of tables and trees in the context of delegate.

class QEXT_MVVM_API QEXTMvvmEditorFactoryInterface
{
public:
    virtual ~QEXTMvvmEditorFactoryInterface() = default;

    virtual std::unique_ptr<QEXTMvvmCustomEditor> createEditor(const QModelIndex& index) const = 0;
};

} // namespace ModelView

#endif // _QEXTMVVMEDITORSEDITORFACTORYINTERFACE_H
