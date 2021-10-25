#include <qextMvvmBoolEditor.h>

#include <QCheckBox>
#include <QHBoxLayout>
#include <QDebug>

const char *g_trueText = "True";
const char *g_falseText = "False";

QEXTMvvmBoolEditor::QEXTMvvmBoolEditor(QWidget *parent)
    : QEXTMvvmCustomEditor(parent)
{
    this->setAutoFillBackground(true);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(4, 0, 0, 0);
    layout->addWidget(m_checkBox);
    this->setLayout(layout);

    connect(m_checkBox, SIGNAL(toggled(bool)), this, SLOT(onCheckBoxChange(bool)));
    this->setFocusProxy(m_checkBox);
    m_checkBox->setText(g_trueText);
}

QEXTMvvmBoolEditor::~QEXTMvvmBoolEditor()
{

}

bool QEXTMvvmBoolEditor::isPersistent() const
{
    return true;
}

void QEXTMvvmBoolEditor::onCheckBoxChange(bool value)
{
    if (value != m_data.value<bool>())
    {
        this->setDataIntern(QVariant(value));
    }
}

void QEXTMvvmBoolEditor::updateComponents()
{
    if (m_data.type() != QVariant::Bool)
    {
        qCritical() << "QEXTMvvmBoolEditor::updateComponents(): Wrong variant type";
        return;
    }

    bool value = m_data.value<bool>();
    m_checkBox->blockSignals(true);
    m_checkBox->setChecked(value);
    m_checkBox->setText(value ? g_trueText : g_falseText);
    m_checkBox->blockSignals(false);
}
