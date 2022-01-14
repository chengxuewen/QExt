// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QToolButton>
#include <qextMvvmCustomEventFilters.h>
#include <qextMvvmExternalPropertyEditor.h>
#include <qextMvvmStyleUtils.h>
#include <qextMvvmCustomVariants.h>
#include <qextMvvmExternalProperty.h>
#include <stdexcept>

using namespace ModelView;

QEXTMvvmExternalPropertyEditor::QEXTMvvmExternalPropertyEditor(QWidget* parent)
    : QEXTMvvmCustomEditor(parent)
    , m_textLabel(new QLabel)
    , m_pixmapLabel(new QLabel)
    , m_focusFilter(new QEXTMvvmLostFocusFilter(this))

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
    connect(button, &QToolButton::clicked, this, &QEXTMvvmExternalPropertyEditor::buttonClicked);

    setLayout(layout);
}

void QEXTMvvmExternalPropertyEditor::setCallback(std::function<void(const QVariant&)> callback)
{
    m_callback = std::move(callback);
}

void QEXTMvvmExternalPropertyEditor::buttonClicked()
{
    if (m_callback)
        m_callback(m_data);
    else
        QMessageBox::warning(nullptr, "Not configured", "No external dialog configured.");
}

void QEXTMvvmExternalPropertyEditor::update_components()
{
    if (!QEXTMvvmUtils::IsExtPropertyVariant(m_data))
        throw std::runtime_error("Error. Wrong variant type (ExternalProperty is required).");

    auto prop = m_data.value<QEXTMvvmExternalProperty>();
    QPixmap pixmap(QEXTMvvmStyle::DefaultPixmapSize(), QEXTMvvmStyle::DefaultPixmapSize());
    pixmap.fill(prop.color());
    m_textLabel->setText(QString::fromStdString(prop.text()));
    m_pixmapLabel->setPixmap(pixmap);
}
