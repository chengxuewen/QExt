#include <qextMvvmExternalPropertyEditor.h>

#include <cfMvvmExternalProperty.h>

#include <cfLog.h>

#include <QHBoxLayout>
#include <QToolButton>
#include <QMessageBox>

Q_DECLARE_METATYPE(CFMvvmExternalProperty)

QEXTMvvmExternalPropertyEditor::QEXTMvvmExternalPropertyEditor(QWidget *parent)
    : QEXTMvvmCustomEditor(parent),
      m_textLabel(new QLabel),
      m_pixmapLabel(new QLabel),
      m_focusFilter(new QEXTMvvmLostFocusFilter(this))
{
    this->setMouseTracking(true);
    this->setAutoFillBackground(true);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(4, 0, 0, 0);

    QToolButton *button = new QToolButton;
    button->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred));
    button->setText(QLatin1String(" . . . "));
    button->setToolTip("Open selector");
    layout->addWidget(m_pixmapLabel);
    layout->addWidget(m_textLabel);
    layout->addStretch(1);
    layout->addWidget(button);
    this->setFocusPolicy(Qt::StrongFocus);
    this->setAttribute(Qt::WA_InputMethodEnabled);
    connect(button, SIGNAL(clicked(bool)), this, SLOT(buttonClicked()));
    this->setLayout(layout);
}

QEXTMvvmExternalPropertyEditor::~QEXTMvvmExternalPropertyEditor()
{

}

void QEXTMvvmExternalPropertyEditor::setCallback(Callback callback)
{
    m_callback = callback;
}

void QEXTMvvmExternalPropertyEditor::buttonClicked()
{
    if (!m_callback.isValid())
    {
        m_callback(m_data);
    }
    else
    {
        QMessageBox::warning(QEXT_DECL_NULLPTR, "Not configured", "No external dialog configured.");
    }
}

void QEXTMvvmExternalPropertyEditor::updateComponents()
{
    if (!m_data.canConvert<CFMvvmExternalProperty>())
    {
        throw std::runtime_error("Error. Wrong variant type (ExternalProperty is required).");
    }

    CFMvvmExternalProperty prop = m_data.value<CFMvvmExternalProperty>();
    QPixmap pixmap(16, 16);
    pixmap.fill(QColor(QString::fromStdString(prop.color())));
    m_textLabel->setText(QString::fromStdString(prop.text()));
    m_pixmapLabel->setPixmap(pixmap);
}
