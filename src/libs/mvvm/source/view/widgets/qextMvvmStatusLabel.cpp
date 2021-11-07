#include <QColor>
#include <QFont>
#include <QPainter>
#include <qextMvvmStyleUtils.h>
#include <qextMvvmStatusLabel.h>
#include <qextMvvmWidgetUtils.h>



QEXTMvvmStatusLabel::QEXTMvvmStatusLabel(QWidget* parent)
    : QFrame(parent), m_font("Monospace", Style::DefaultInfoBarTextSize(), QFont::Normal, false)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setFixedHeight(Style::DefaultInfoBarHeight());
}

void QEXTMvvmStatusLabel::setText(const QString& text)
{
    m_text = text;
    update();
}

void QEXTMvvmStatusLabel::setFont(const QFont& font)
{
    m_font = font;
    update();
}

void QEXTMvvmStatusLabel::setPointSize(int pointSize)
{
    m_font.setPointSize(pointSize);
    update();
}

void QEXTMvvmStatusLabel::setAlignment(Qt::Alignment alignment)
{
    m_alignment = alignment;
    update();
}

void QEXTMvvmStatusLabel::paintEvent(QPaintEvent* event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);
    painter.setBrush(QColor(Qt::black));
    painter.setPen(QColor(Qt::black));
    painter.setFont(m_font);

    QRect bbox(0, 0, geometry().width(), geometry().height());
    const int gap(QEXTMvvmWidgetUtils::WidthOfLetterM() / 2); // make it smaller
    auto textRect = bbox.adjusted(gap, 0, gap, 0);

    painter.fillRect(bbox, QColor(Qt::white));
    painter.drawText(textRect, static_cast<int>(m_alignment), m_text);
}
