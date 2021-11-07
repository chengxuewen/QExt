#ifndef _QEXTMVVMEDITORFACTORYINTERFACE_H
#define _QEXTMVVMEDITORFACTORYINTERFACE_H

#include <memory>
#include <qextMvvmGlobal.h>
#include <string>

class QModelIndex;
class QWidget;


class QEXTMvvmCustomEditor;

//! Interface for custom editor factory.
//! Intended for editor construction in cells of tables and trees in the context of delegate.

class QEXT_MVVM_API QEXTMvvmEditorFactoryInterface
{
public:
    virtual ~QEXTMvvmEditorFactoryInterface() { }

    virtual QEXTMvvmCustomEditor *createEditor(const QModelIndex &index) const = 0;
};


#endif // _QEXTMVVMEDITORFACTORYINTERFACE_H
