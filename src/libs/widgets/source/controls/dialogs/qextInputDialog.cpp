#include <qextInputDialog.h>

QExtInputDialog::QExtInputDialog(QWidget *parent, Qt::WindowFlags flags)
    : QInputDialog(parent, flags)
{
}

QExtInputDialog::~QExtInputDialog()
{
}

QString QExtInputDialog::getItem(QWidget *parent, const QString &title, const QString &label, const QStringList &items,
                                 int current, bool editable, bool *ok, Qt::WindowFlags flags,
                                 Qt::InputMethodHints inputMethodHints)
{
    QString text(items.value(current));

    QInputDialog dialog(parent, flags);
    dialog.setWindowTitle(title);
    dialog.setLabelText(label);
    dialog.setComboBoxItems(items);
    dialog.setTextValue(text);
    dialog.setComboBoxEditable(editable);
    dialog.setInputMethodHints(inputMethodHints);
    dialog.setOptions(QInputDialog::UseListViewForComboBoxItems);
    dialog.setWindowFlag(Qt::WindowContextHelpButtonHint, false);

    const int ret = dialog.exec();
    if (ok)
    {
        *ok = !!ret;
    }
    if (ret)
    {
        return dialog.textValue();
    }
    else
    {
        return text;
    }
}
