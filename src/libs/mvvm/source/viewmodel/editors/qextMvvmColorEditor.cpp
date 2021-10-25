#include <qextMvvmColorEditor.h>

#include <QColorDialog>
#include <QHBoxLayout>
#include <QDebug>

QEXTMvvmColorEditor::QEXTMvvmColorEditor(QWidget *parent)
    : QEXTMvvmCustomEditor(parent),
      m_textLabel(QEXT_DECL_NULLPTR),
      m_pixmapLabel(new QLabel),
      m_focusFilter(new QEXTMvvmLostFocusFilter(this))
{
    this->setMouseTracking(true);
    this->setAutoFillBackground(true);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(4, 0, 0, 0);
    layout->addWidget(m_pixmapLabel);
    //    layout->addWidget(m_textLabel); // no color name, only color rectangle
    layout->addStretch(1);
    setLayout(layout);

    this->setFocusPolicy(Qt::StrongFocus);
    this->setAttribute(Qt::WA_InputMethodEnabled);
}

QEXTMvvmColorEditor::~QEXTMvvmColorEditor()
{

}

void QEXTMvvmColorEditor::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    // temporarily installing filter to prevent loss of focus caused by too insistent dialog
    this->installEventFilter(m_focusFilter);

    QColor newColor = QColorDialog::getColor(this->currentColor());

    this->removeEventFilter(m_focusFilter);

    if (newColor.isValid())
    {
        this->setDataIntern(newColor);
        this->updateComponents();
    }
}

void QEXTMvvmColorEditor::updateComponents()
{
    if (m_data.type() == QVariant::Color)
    {
        qCritical() << "QEXTMvvmColorEditor::updateComponents()(): Wrong variant type";
        return;
    }

    QPixmap pixmap(16, 16);
    pixmap.fill(this->currentColor());
    //    m_textLabel->setText(currentColor().name());
    m_pixmapLabel->setPixmap(pixmap);
}

QColor QEXTMvvmColorEditor::currentColor() const
{
    return m_data.value<QColor>();
}
