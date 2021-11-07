#include <cmath>
#include <qextMvvmBoolEditor.h>
#include <qextMvvmColorEditor.h>
#include <qextMvvmComboPropertyEditor.h>
#include <qextMvvmDoubleEditor.h>
#include <qextMvvmEditorConstants.h>
#include <qextMvvmEditorBuilders.h>
#include <qextMvvmExternalPropertyEditor.h>
#include <qextMvvmIntegerEditor.h>
#include <qextMvvmScientificDoubleEditor.h>
#include <qextMvvmScientificSpinboxEditor.h>
#include <qextMvvmSelectableComboboxEditor.h>
#include <qextMvvmUtils.h>
#include <qextMvvmItem.h>
#include <qextMvvmRealLimits.h>

namespace
{
    double qextMvvmSingleStep(int decimals)
    {
        // For item with decimals=3 (i.e. 0.001) single step will be 0.1
        return 1. / std::pow(10., decimals - 1);
    }

    double qextMvvmGetStep(double val)
    {
        return val == 0.0 ? 1.0 : val / 100.;
    }

    QEXTMvvmCustomEditor *qextMvvmBoolEditorBuilder(const QEXTMvvmItem *)
    {
        return new QEXTMvvmBoolEditor;
    }

    QEXTMvvmCustomEditor *qextMvvmIntegerEditorBuilder(const QEXTMvvmItem *item)
    {
        QEXTMvvmIntegerEditor *editor = new QEXTMvvmIntegerEditor;
        if (item && item->hasData(QEXTMvvmItem::Role_Limits))
        {
            QEXTMvvmRealLimits limits = item->data<QEXTMvvmRealLimits>(QEXTMvvmItem::Role_Limits);
            editor->setRange(limits.lowerLimit(), limits.upperLimit());
        }
        return editor;
    }

    QEXTMvvmCustomEditor *qextMvvmDoubleEditorBuilder(const QEXTMvvmItem *item)
    {
        QEXTMvvmDoubleEditor *editor = new QEXTMvvmDoubleEditor;
        if (item && item->hasData(QEXTMvvmItem::Role_Limits))
        {
            QEXTMvvmRealLimits limits = item->data<QEXTMvvmRealLimits>(QEXTMvvmItem::Role_Limits);
            editor->setRange(limits.lowerLimit(), limits.upperLimit());
            editor->setSingleStep(qextMvvmSingleStep(QEXTMvvmConstants::default_double_decimals));
            editor->setDecimals(QEXTMvvmConstants::default_double_decimals);
        }
        return editor;
    }

    QEXTMvvmCustomEditor *qextMvvmScientificDoubleEditorBuilder(const QEXTMvvmItem *item)
    {
        QEXTMvvmScientificDoubleEditor *editor = new QEXTMvvmScientificDoubleEditor;
        if (item && item->hasData(QEXTMvvmItem::Role_Limits))
        {
            auto limits = item->data<QEXTMvvmRealLimits>(QEXTMvvmItem::Role_Limits);
            editor->setRange(limits.lowerLimit(), limits.upperLimit());
        }
        return editor;
    }

    QEXTMvvmCustomEditor *qextMvvmScientificSpinBoxEditorBuilder(const QEXTMvvmItem *item)
    {
        QEXTMvvmScientificSpinBoxEditor *editor = new QEXTMvvmScientificSpinBoxEditor;
        if (item)
        {
            if (item->hasData(QEXTMvvmItem::Role_Limits))
            {
                auto limits = item->data<QEXTMvvmRealLimits>(QEXTMvvmItem::Role_Limits);
                editor->setRange(limits.lowerLimit(), limits.upperLimit());
            }
            editor->setSingleStep(qextMvvmGetStep(item->data<double>()));
        }
        editor->setDecimals(QEXTMvvmConstants::default_double_decimals);
        return editor;
    }

    QEXTMvvmCustomEditor *qextMvvmColorEditorBuilder(const QEXTMvvmItem *)
    {
        return new QEXTMvvmColorEditor;
    }

    QEXTMvvmCustomEditor *qextMvvmComboPropertyEditorBuilder(const QEXTMvvmItem *)
    {
        return new QEXTMvvmComboPropertyEditor;
    }

    QEXTMvvmCustomEditor *qextMvvmExternalPropertyEditorBuilder(const QEXTMvvmItem *)
    {
        return new QEXTMvvmExternalPropertyEditor;
    }

    QEXTMvvmCustomEditor *qextMvvmSelectableComboPropertyEditorBuilder(const QEXTMvvmItem *)
    {
        return new QEXTMvvmSelectableComboBoxEditor;
    }


} // namespace


QEXTMvvmEditorBuilders::EditorBuilder QEXTMvvmEditorBuilders::boolEditorBuilder()
{
    return EditorBuilder(qextMvvmBoolEditorBuilder);
}

QEXTMvvmEditorBuilders::EditorBuilder QEXTMvvmEditorBuilders::integerEditorBuilder()
{
    return EditorBuilder(qextMvvmIntegerEditorBuilder);
}

QEXTMvvmEditorBuilders::EditorBuilder QEXTMvvmEditorBuilders::doubleEditorBuilder()
{
    return EditorBuilder(qextMvvmDoubleEditorBuilder);
}

QEXTMvvmEditorBuilders::EditorBuilder QEXTMvvmEditorBuilders::scientificDoubleEditorBuilder()
{
    return EditorBuilder(qextMvvmScientificDoubleEditorBuilder);
}

QEXTMvvmEditorBuilders::EditorBuilder QEXTMvvmEditorBuilders::scientificSpinBoxEditorBuilder()
{
    return EditorBuilder(qextMvvmScientificSpinBoxEditorBuilder);
}

QEXTMvvmEditorBuilders::EditorBuilder QEXTMvvmEditorBuilders::colorEditorBuilder()
{
    return EditorBuilder(qextMvvmColorEditorBuilder);
}

QEXTMvvmEditorBuilders::EditorBuilder QEXTMvvmEditorBuilders::comboPropertyEditorBuilder()
{
    return EditorBuilder(qextMvvmComboPropertyEditorBuilder);
}

QEXTMvvmEditorBuilders::EditorBuilder QEXTMvvmEditorBuilders::externalPropertyEditorBuilder()
{
    return EditorBuilder(qextMvvmExternalPropertyEditorBuilder);
}

QEXTMvvmEditorBuilders::EditorBuilder QEXTMvvmEditorBuilders::selectableComboPropertyEditorBuilder()
{
    return EditorBuilder(qextMvvmSelectableComboPropertyEditorBuilder);
}
