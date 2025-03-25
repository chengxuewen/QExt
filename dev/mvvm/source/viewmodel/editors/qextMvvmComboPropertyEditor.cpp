// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmComboPropertyEditor.h>
#include <qextMvvmComboProperty.h>
#include <QComboBox>
#include <QVBoxLayout>

namespace {
QStringList toList(const std::vector<std::string>& container)
{
    QStringList result;
    for (const auto& str : container)
        result.push_back(QString::fromStdString(str));
    return result;
}
} // namespace

using namespace ModelView;

QExtMvvmComboPropertyEditor::QExtMvvmComboPropertyEditor(QWidget* parent)
    : QExtMvvmCustomEditor(parent), m_box(new QComboBox)
{
    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    auto layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(m_box);
    setLayout(layout);

    setConnected(true);
}

QSize QExtMvvmComboPropertyEditor::sizeHint() const
{
    return m_box->sizeHint();
}

QSize QExtMvvmComboPropertyEditor::minimumSizeHint() const
{
    return m_box->minimumSizeHint();
}

bool QExtMvvmComboPropertyEditor::is_persistent() const
{
    return true;
}

void QExtMvvmComboPropertyEditor::onIndexChanged(int index)
{
    auto comboProperty = m_data.value<QExtMvvmComboProperty>();

    if (comboProperty.currentIndex() != index) {
        comboProperty.setCurrentIndex(index);
        setDataIntern(QVariant::fromValue<QExtMvvmComboProperty>(comboProperty));
    }
}

void QExtMvvmComboPropertyEditor::update_components()
{
    setConnected(false);

    m_box->clear();
    m_box->insertItems(0, toList(internLabels()));
    m_box->setCurrentIndex(internIndex());

    setConnected(true);
}

//! Returns list of labels for QComboBox

std::vector<std::string> QExtMvvmComboPropertyEditor::internLabels()
{
    if (!m_data.canConvert<QExtMvvmComboProperty>())
        return {};
    auto comboProperty = m_data.value<QExtMvvmComboProperty>();
    return comboProperty.values();
}

//! Returns index for QComboBox.

int QExtMvvmComboPropertyEditor::internIndex()
{
    if (!m_data.canConvert<QExtMvvmComboProperty>())
        return 0;
    auto comboProperty = m_data.value<QExtMvvmComboProperty>();
    return comboProperty.currentIndex();
}

void QExtMvvmComboPropertyEditor::setConnected(bool isConnected)
{
    if (isConnected)
        connect(m_box, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,
                &QExtMvvmComboPropertyEditor::onIndexChanged, Qt::UniqueConnection);
    else
        disconnect(m_box, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                   this, &QExtMvvmComboPropertyEditor::onIndexChanged);
}
