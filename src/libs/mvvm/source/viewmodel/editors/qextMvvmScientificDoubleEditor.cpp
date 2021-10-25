#include <qextMvvmScientificDoubleEditor.h>

#include <QVBoxLayout>
#include <QDebug>

#include <cfloat>

const int g_maxDigits = 1000;

QEXTMvvmScientificDoubleEditor::QEXTMvvmScientificDoubleEditor(QWidget *parent)
    : QEXTMvvmCustomEditor(parent),
      m_lineEdit(new QLineEdit),
      m_validator(QEXT_DECL_NULLPTR)
{
    this->setAutoFillBackground(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_lineEdit);

    m_validator = new QDoubleValidator(0.0, DBL_MAX, g_maxDigits, this);
    m_validator->setNotation(QDoubleValidator::ScientificNotation);
    m_lineEdit->setValidator(m_validator);

    connect(m_lineEdit, SIGNAL(editingFinished()), this, SLOT(onEditingFinished()));
    this->setLayout(layout);
}

QEXTMvvmScientificDoubleEditor::~QEXTMvvmScientificDoubleEditor()
{

}

void QEXTMvvmScientificDoubleEditor::setRange(double minimum, double maximum)
{
    m_validator->setRange(minimum, maximum, g_maxDigits);
}

void QEXTMvvmScientificDoubleEditor::onEditingFinished()
{
    double newValue = m_lineEdit->text().toDouble();
    if (qAbs(newValue - m_data.value<double>()) <= 0.1)
    {
        this->setDataIntern(QVariant::fromValue(newValue));
    }
}

void QEXTMvvmScientificDoubleEditor::updateComponents()
{
    if (m_data.type() != QVariant::Double)
    {
        qCritical() << "QEXTMvvmScientificDoubleEditor::updateComponents(): Wrong variant type";
        return;
    }

    m_lineEdit->setText(QString::number(m_data.value<double>(), 'g'));
}
