#include <qextMvvmEditorBuilders.h>
#include <qextMvvmExternalPropertyComboEditor.h>
#include <qextMvvmExternalPropertyEditor.h>
#include <qextMvvmBoolEditor.h>
#include <qextMvvmDoubleEditor.h>
#include <qextMvvmIntegerEditor.h>
#include <qextMvvmColorEditor.h>
#include <qextMvvmComboPropertyEditor.h>
#include <qextMvvmScientificDoubleEditor.h>
#include <qextMvvmScientificSpinBoxEditor.h>
#include <qextMvvmSelectableComboBoxEditor.h>
#include <qextMvvmConstants.h>

#include <cfMvvmRealLimits.h>

#include <cfPointerFunctor.h>

#include <cmath>

double qextMvvmSingleStep(int decimals)
{
    // For item with decimals=3 (i.e. 0.001) single step will be 0.1
    return 1.0 / std::pow(10., decimals - 1);
}

double qextMvvmGetStep(double val)
{
    return val == 0.0 ? 1.0 : val / 100.;
}

CFUniquePointer<QEXTMvvmCustomEditor> qextMvvmBuildBoolEditor(CFMvvmItem *item)
{
    CF_UNUSED(item);
    CFUniquePointer<QEXTMvvmCustomEditor> editor(new QEXTMvvmBoolEditor);
    return editor;
}

CFUniquePointer<QEXTMvvmCustomEditor> qextMvvmBuildIntegerEditor(CFMvvmItem *item)
{
    QEXTMvvmIntegerEditor *editor = new QEXTMvvmIntegerEditor;
    if (item && item->hasData(CFMvvmItem::Role_Limits))
    {
        CFMvvmRealLimits limits = item->data<CFMvvmRealLimits>(CFMvvmItem::Role_Limits);
        editor->setRange(limits.lowerLimit(), limits.upperLimit());
    }
    return CFUniquePointer<QEXTMvvmCustomEditor>(editor);
}

CFUniquePointer<QEXTMvvmCustomEditor> qextMvvmBuildDoubleEditor(CFMvvmItem *item)
{
    QEXTMvvmDoubleEditor *editor = new QEXTMvvmDoubleEditor;
    if (item && item->hasData(CFMvvmItem::Role_Limits))
    {
        CFMvvmRealLimits limits = item->data<CFMvvmRealLimits>(CFMvvmItem::Role_Limits);
        editor->setRange(limits.lowerLimit(), limits.upperLimit());
        editor->setSingleStep(qextMvvmSingleStep(QEXTMvvmConstants::default_double_decimals));
        editor->setDecimals(QEXTMvvmConstants::default_double_decimals);
    }
    return CFUniquePointer<QEXTMvvmCustomEditor>(editor);
}

CFUniquePointer<QEXTMvvmCustomEditor> qextMvvmBuildScientificDoubleEditor(CFMvvmItem *item)
{
    QEXTMvvmScientificDoubleEditor *editor = new QEXTMvvmScientificDoubleEditor;
    if (item && item->hasData(CFMvvmItem::Role_Limits))
    {
        CFMvvmRealLimits limits = item->data<CFMvvmRealLimits>(CFMvvmItem::Role_Limits);
        editor->setRange(limits.lowerLimit(), limits.upperLimit());
    }
    return CFUniquePointer<QEXTMvvmCustomEditor>(editor);
}

CFUniquePointer<QEXTMvvmCustomEditor> qextMvvmBuildScientificSpinBoxEditor(CFMvvmItem *item)
{
    QEXTMvvmScientificSpinBoxEditor *editor = new QEXTMvvmScientificSpinBoxEditor;
    if (item)
    {
        if (item->hasData(CFMvvmItem::Role_Limits))
        {
            CFMvvmRealLimits limits = item->data<CFMvvmRealLimits>(CFMvvmItem::Role_Limits);
            editor->setRange(limits.lowerLimit(), limits.upperLimit());
        }
        editor->setSingleStep(qextMvvmGetStep(item->data<double>()));
    }
    editor->setDecimals(QEXTMvvmConstants::default_double_decimals);
    return CFUniquePointer<QEXTMvvmCustomEditor>(editor);
}

CFUniquePointer<QEXTMvvmCustomEditor> qextMvvmBuildColorEditor(CFMvvmItem *item)
{
    CF_UNUSED(item);
    CFUniquePointer<QEXTMvvmCustomEditor> editor(new QEXTMvvmColorEditor);
    return editor;
}

CFUniquePointer<QEXTMvvmCustomEditor> qextMvvmBuildComboPropertyEditor(CFMvvmItem *item)
{
    CF_UNUSED(item);
    CFUniquePointer<QEXTMvvmCustomEditor> editor(new QEXTMvvmComboPropertyEditor);
    return editor;
}

CFUniquePointer<QEXTMvvmCustomEditor> qextMvvmBuildExternalPropertyEditor(CFMvvmItem *item)
{
    CF_UNUSED(item);
    CFUniquePointer<QEXTMvvmCustomEditor> editor(new QEXTMvvmExternalPropertyEditor);
    return editor;
}

CFUniquePointer<QEXTMvvmCustomEditor> qextMvvmBuildSelectableComboPropertyEditor(CFMvvmItem *item)
{
    CFUniquePointer<QEXTMvvmCustomEditor> editor(new QEXTMvvmSelectableComboBoxEditor);
    return editor;
}

QEXTMvvmEditorBuilders::QEXTMvvmEditorBuilders()
{

}

QEXTMvvmEditorBuilders::Builder QEXTMvvmEditorBuilders::boolEditorBuilder()
{
    Builder builder = cfPointerFunctor(&qextMvvmBuildBoolEditor);
    return builder;
}

QEXTMvvmEditorBuilders::Builder QEXTMvvmEditorBuilders::integerEditorBuilder()
{
    Builder builder = cfPointerFunctor(&qextMvvmBuildIntegerEditor);
    return builder;
}

QEXTMvvmEditorBuilders::Builder QEXTMvvmEditorBuilders::doubleEditorBuilder()
{
    Builder builder = cfPointerFunctor(&qextMvvmBuildDoubleEditor);
    return builder;
}

QEXTMvvmEditorBuilders::Builder QEXTMvvmEditorBuilders::scientificDoubleEditorBuilder()
{
    Builder builder = cfPointerFunctor(&qextMvvmBuildScientificDoubleEditor);
    return builder;
}

QEXTMvvmEditorBuilders::Builder QEXTMvvmEditorBuilders::scientificSpinBoxEditorBuilder()
{
    Builder builder = cfPointerFunctor(&qextMvvmBuildScientificSpinBoxEditor);
    return builder;
}

QEXTMvvmEditorBuilders::Builder QEXTMvvmEditorBuilders::colorEditorBuilder()
{
    Builder builder = cfPointerFunctor(&qextMvvmBuildColorEditor);
    return builder;
}

QEXTMvvmEditorBuilders::Builder QEXTMvvmEditorBuilders::comboPropertyEditorBuilder()
{
    Builder builder = cfPointerFunctor(&qextMvvmBuildComboPropertyEditor);
    return builder;
}

QEXTMvvmEditorBuilders::Builder QEXTMvvmEditorBuilders::externalPropertyEditorBuilder()
{
    Builder builder = cfPointerFunctor(&qextMvvmBuildExternalPropertyEditor);
    return builder;
}

QEXTMvvmEditorBuilders::Builder QEXTMvvmEditorBuilders::selectableComboPropertyEditorBuilder()
{
    Builder builder = cfPointerFunctor(&qextMvvmBuildSelectableComboPropertyEditor);
    return builder;
}
