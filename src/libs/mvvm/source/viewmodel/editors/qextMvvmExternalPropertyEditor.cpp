#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QToolButton>
#include <qextMvvmCustomEventFilters.h>
#include <qextMvvmExternalPropertyEditor.h>
#include <qextMvvmStyleUtils.h>
#include <qextMvvmUtils.h>
#include <qextMvvmExternalProperty.h>
#include <stdexcept>



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

void QEXTMvvmExternalPropertyEditor::setCallback(QEXTFunction<void, const QVariant &> callback)
{
    m_callback = callback;
}

void QEXTMvvmExternalPropertyEditor::buttonClicked()
{
    if (m_callback.isValid())
        m_callback(m_data);
    else
        QMessageBox::warning(nullptr, "Not configured", "No external dialog configured.");
}

void QEXTMvvmExternalPropertyEditor::updateComponents()
{
    if (!QEXTMvvmUtils::IsExtPropertyVariant(m_data))
        throw std::runtime_error("Error. Wrong variant type (QEXTMvvmExternalProperty is required).");

    auto prop = m_data.value<QEXTMvvmExternalProperty>();
    QPixmap pixmap(Style::DefaultPixmapSize(), Style::DefaultPixmapSize());
    pixmap.fill(prop.color());
    m_textLabel->setText(prop.text());
    m_pixmapLabel->setPixmap(pixmap);
}
