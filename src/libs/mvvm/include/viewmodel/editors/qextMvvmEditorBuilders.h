#ifndef _QEXTMVVMEDITORBUILDERS_H
#define _QEXTMVVMEDITORBUILDERS_H

#include <qextFunction.h>
#include <qextMvvmGlobal.h>

class QEXTMvvmCustomEditor;
class QEXTMvvmItem;

//! Collection of methods to build custom editors for trees/tables cells.
//! Used to edit QEXTMvvmItem data in the context of QEXTMvvmDefaultEditorFactory.

struct QEXT_MVVM_API QEXTMvvmEditorBuilders
{
    typedef QEXTFunction<QEXTMvvmCustomEditor *, const QEXTMvvmItem *> EditorBuilder;

    //! Builder for boolean property editor.
    static EditorBuilder boolEditorBuilder();

    //! Builder for integer property editor.
    static EditorBuilder integerEditorBuilder();

    //! Builder for double editor with limits support.
    static EditorBuilder doubleEditorBuilder();

    //! Builder for double editor with scientific notation based on simple text field.
    static EditorBuilder scientificDoubleEditorBuilder();

    //! Builder for double editor with scientific notation and spinbox functionality.
    static EditorBuilder scientificSpinBoxEditorBuilder();

    //! Builder for color property editor.
    static EditorBuilder colorEditorBuilder();

    //! Builder for QEXTMvvmComboProperty editor.
    static EditorBuilder comboPropertyEditorBuilder();

    //! Builder for external property editor.
    static EditorBuilder externalPropertyEditorBuilder();

    //! Builder for QEXTMvvmComboProperty editor with multi-selection functionality.
    static EditorBuilder selectableComboPropertyEditorBuilder();

};

#endif // _QEXTMVVMEDITORBUILDERS_H
