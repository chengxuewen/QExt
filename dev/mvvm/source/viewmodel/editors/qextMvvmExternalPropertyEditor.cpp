// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmExternalPropertyEditor.h>
#include <qextMvvmCustomEventFilters.h>
#include <qextMvvmStyleUtils.h>
#include <qextMvvmCustomVariants.h>
#include <qextMvvmExternalProperty.h>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QToolButton>
#include <stdexcept>

using namespace ModelView;

QExtMvvmExternalPropertyEditor::QExtMvvmExternalPropertyEditor(QWidget* parent)
    : QExtMvvmCustomEditor(parent)
    , m_textLabel(new QLabel)
    , m_pixmapLabel(new QLabel)
    , m_focusFilter(new QExtMvvmLostFocusFilter(this))

{
    setMouseTracking(true);
    setAutoFillBackground(true);

    auto layout = new QHBoxLayout;
    layout->setContentsMargins(4, 0, 0, 0);

    auto button = new QToolButton;
    button->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred));
    button->setText(QLatin1String(" . . . "));
    button->setToolTip("Open selector");
    layout->addWidget(m_pixmapLabel);
    layout->addWidget(m_textLabel);
    layout->addStretch(1);
    layout->addWidget(button);
    setFocusPolicy(Qt::StrongFocus);
    setAttribute(Qt::WA_InputMethodEnabled);
    connect(button, &QToolButton::clicked, this, &QExtMvvmExternalPropertyEditor::buttonClicked);

    setLayout(layout);
}

void QExtMvvmExternalPropertyEditor::setCallback(std::function<void(const QVariant&)> callback)
{
    m_callback = std::move(callback);
}

void QExtMvvmExternalPropertyEditor::buttonClicked()
{
    if (m_callback)
        m_callback(m_data);
    else
        QMessageBox::warning(nullptr, "Not configured", "No external dialog configured.");
}

void QExtMvvmExternalPropertyEditor::update_components()
{
    if (!Utils::IsExtPropertyVariant(m_data))
        throw std::runtime_error("Error. Wrong variant type (QExtMvvmExternalProperty is required).");

    auto prop = m_data.value<QExtMvvmExternalProperty>();
    QPixmap pixmap(Style::DefaultPixmapSize(), Style::DefaultPixmapSize());
    pixmap.fill(prop.color());
    m_textLabel->setText(QString::fromStdString(prop.text()));
    m_pixmapLabel->setPixmap(pixmap);
}
