#ifndef _QEXTMVVMEDITORFACTORYINTERFACE_H
#define _QEXTMVVMEDITORFACTORYINTERFACE_H

#include <qextMvvmGlobal.h>
#include <qextMvvmCustomEditor.h>

#include <cfUniquePointer.h>

class QModelIndex;
class QWidget;

CF_BEGIN_NAMESPACE

//! Interface for custom editor factory.
//! Intended for editor construction in cells of tables and trees in the context of delegate.

class CustomEditor;
class QEXT_MVVM_API QEXTMvvmEditorFactoryInterface
{
public:
    virtual ~QEXTMvvmEditorFactoryInterface() { }

    virtual CFUniquePointer<QEXTMvvmCustomEditor> createEditor(const QModelIndex &index) const = 0;
};

CF_END_NAMESPACE

#endif // _QEXTMVVMEDITORFACTORYINTERFACE_H
