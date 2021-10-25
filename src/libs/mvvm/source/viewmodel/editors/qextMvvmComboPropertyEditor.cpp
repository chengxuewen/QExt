#include <qextMvvmComboPropertyEditor.h>

#include <cfMvvmComboProperty.h>

#include <QVBoxLayout>

Q_DECLARE_METATYPE(CFMvvmComboProperty)

QStringList qextMvvmToList(const std::vector<std::string> &container)
{
    QStringList result;
    std::vector<std::string>::const_iterator iter;
    for (iter = container.begin(); iter != container.end(); ++iter)
    {
        result.push_back(QString::fromStdString(*iter));
    }
    return result;
}

QEXTMvvmComboPropertyEditor::QEXTMvvmComboPropertyEditor(QWidget *parent)
    : QEXTMvvmCustomEditor(parent),
      m_box(new QComboBox)
{
    this->setAutoFillBackground(true);
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_box);
    this->setLayout(layout);
    this->setConnected(true);
}

QEXTMvvmComboPropertyEditor::~QEXTMvvmComboPropertyEditor()
{

}

QSize QEXTMvvmComboPropertyEditor::sizeHint() const
{
    return m_box->sizeHint();
}

QSize QEXTMvvmComboPropertyEditor::minimumSizeHint() const
{
    return m_box->minimumSizeHint();
}

bool QEXTMvvmComboPropertyEditor::isPersistent() const
{
    return true;
}

void QEXTMvvmComboPropertyEditor::onIndexChanged(int index)
{
    CFMvvmComboProperty comboProperty = m_data.value<CFMvvmComboProperty>();
    if (comboProperty.currentIndex() != index)
    {
        comboProperty.setCurrentIndex(index);
        this->setDataIntern(QVariant::fromValue<CFMvvmComboProperty>(comboProperty));
    }
}

void QEXTMvvmComboPropertyEditor::updateComponents()
{
    this->setConnected(false);

    m_box->clear();
    m_box->insertItems(0, qextMvvmToList(this->internLabels()));
    m_box->setCurrentIndex(this->internIndex());

    this->setConnected(true);
}

std::vector<std::string> QEXTMvvmComboPropertyEditor::internLabels()
{
    std::vector<std::string> result;
    if (!m_data.canConvert<CFMvvmComboProperty>())
    {
        return result;
    }
    CFMvvmComboProperty comboProperty = m_data.value<CFMvvmComboProperty>();
    return comboProperty.values();
}

int QEXTMvvmComboPropertyEditor::internIndex()
{
    if (!m_data.canConvert<CFMvvmComboProperty>())
    {
        return 0;
    }
    CFMvvmComboProperty comboProperty = m_data.value<CFMvvmComboProperty>();
    return comboProperty.currentIndex();
}

void QEXTMvvmComboPropertyEditor::setConnected(bool isConnected)
{
    if (isConnected)
    {
        connect(m_box, SIGNAL(currentIndexChanged(int)), this, SLOT(onIndexChanged(int)), Qt::UniqueConnection);
    }
    else
    {
        disconnect(m_box, SIGNAL(currentIndexChanged(int)), this, SLOT(onIndexChanged(int)));
    }
}
