// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QComboBox>
#include <QVBoxLayout>
#include <qextMvvmComboPropertyEditor.h>
#include <qextMvvmComboProperty.h>

namespace
{
QStringList toList(const std::vector<std::string>& container)
{
    QStringList result;
    for (const auto& str : container)
        result.push_back(QString::fromStdString(str));
    return result;
}
} // namespace

using namespace ModelView;

QEXTMvvmComboPropertyEditor::QEXTMvvmComboPropertyEditor(QWidget* parent)
    : QEXTMvvmCustomEditor(parent), m_box(new QComboBox)
{
    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_box);
    setLayout(layout);

    setConnected(true);
}

QSize QEXTMvvmComboPropertyEditor::sizeHint() const
{
    return m_box->sizeHint();
}

QSize QEXTMvvmComboPropertyEditor::minimumSizeHint() const
{
    return m_box->minimumSizeHint();
}

bool QEXTMvvmComboPropertyEditor::is_persistent() const
{
    return true;
}

void QEXTMvvmComboPropertyEditor::onIndexChanged(int index)
{
    auto comboProperty = m_data.value<QEXTMvvmComboProperty>();

    if (comboProperty.currentIndex() != index) {
        comboProperty.setCurrentIndex(index);
        setDataIntern(QVariant::fromValue<QEXTMvvmComboProperty>(comboProperty));
    }
}

void QEXTMvvmComboPropertyEditor::update_components()
{
    setConnected(false);

    m_box->clear();
    m_box->insertItems(0, toList(internLabels()));
    m_box->setCurrentIndex(internIndex());

    setConnected(true);
}

//! Returns list of labels for QComboBox

std::vector<std::string> QEXTMvvmComboPropertyEditor::internLabels()
{
    if (!m_data.canConvert<QEXTMvvmComboProperty>())
        return {};
    auto comboProperty = m_data.value<QEXTMvvmComboProperty>();
    return comboProperty.values();
}

//! Returns index for QComboBox.

int QEXTMvvmComboPropertyEditor::internIndex()
{
    if (!m_data.canConvert<QEXTMvvmComboProperty>())
        return 0;
    auto comboProperty = m_data.value<QEXTMvvmComboProperty>();
    return comboProperty.currentIndex();
}

void QEXTMvvmComboPropertyEditor::setConnected(bool isConnected)
{
    if (isConnected)
        connect(m_box, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,
                &QEXTMvvmComboPropertyEditor::onIndexChanged, Qt::UniqueConnection);
    else
        disconnect(m_box, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                   this, &QEXTMvvmComboPropertyEditor::onIndexChanged);
}
