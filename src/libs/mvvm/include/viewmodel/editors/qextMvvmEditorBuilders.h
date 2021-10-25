#ifndef _QEXTMVVMEDITORBUILDERS_H
#define _QEXTMVVMEDITORBUILDERS_H

#include <qextMvvmGlobal.h>
#include <qextMvvmCustomEditor.h>
#include <cfMvvmItem.h>

#include <cfUniquePointer.h>
#include <cfSlot.h>

CF_USE_NAMESPACE

class QEXT_MVVM_API QEXTMvvmEditorBuilders
{
public:
    typedef CFUniquePointer<QEXTMvvmCustomEditor> Editor;
    typedef CFSlot<Editor, CFMvvmItem *> Builder;

    QEXTMvvmEditorBuilders();

    //! Builder for boolean property editor.
    static Builder boolEditorBuilder();

    //! Builder for integer property editor.
    static Builder integerEditorBuilder();

    //! Builder for double editor with limits support.
    static Builder doubleEditorBuilder();

    //! Builder for double editor with scientific notation based on simple text field.
    static Builder scientificDoubleEditorBuilder();

    //! Builder for double editor with scientific notation and spinbox functionality.
    static Builder scientificSpinBoxEditorBuilder();

    //! Builder for color property editor.
    static Builder colorEditorBuilder();

    //! Builder for ComboProperty editor.
    static Builder comboPropertyEditorBuilder();

    //! Builder for external property editor.
    static Builder externalPropertyEditorBuilder();

    //! Builder for ComboProperty editor with multi-selection functionality.
    static Builder selectableComboPropertyEditorBuilder();
};

#endif // _QEXTMVVMEDITORBUILDERS_H
