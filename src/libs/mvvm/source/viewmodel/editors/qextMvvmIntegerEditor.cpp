#include <qextMvvmIntegerEditor.h>

#include <QVBoxLayout>
#include <QDebug>

const int g_maxVal = 65536;
const int g_minVal = -g_maxVal;

QEXTMvvmIntegerEditor::QEXTMvvmIntegerEditor(QWidget *parent)
    : QEXTMvvmCustomEditor(parent),
      m_intEditor(new QSpinBox)
{
    this->setAutoFillBackground(true);
    m_intEditor->setFocusPolicy(Qt::StrongFocus);
    m_intEditor->setKeyboardTracking(false);
    m_intEditor->setRange(g_minVal, g_maxVal);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_intEditor);

    connect(m_intEditor, SIGNAL(valueChanged(int)), this, SLOT(onEditingFinished()));

    this->setLayout(layout);
    this->setFocusProxy(m_intEditor);
}

QEXTMvvmIntegerEditor::~QEXTMvvmIntegerEditor()
{

}

void QEXTMvvmIntegerEditor::setRange(int minimum, int maximum)
{
    m_intEditor->setRange(minimum, maximum);
}

void QEXTMvvmIntegerEditor::onEditingFinished()
{
    int newValue = m_intEditor->value();
    if (newValue != m_data.value<int>())
    {
        this->setDataIntern(QVariant::fromValue(newValue));
    }
}

void QEXTMvvmIntegerEditor::updateComponents()
{
    if (m_data.type() != QVariant::Int)
    {
        qCritical() << "QEXTMvvmIntegerEditor::updateComponents(): Wrong variant type";
        return;
    }
    m_intEditor->setValue(m_data.value<int>());
}
