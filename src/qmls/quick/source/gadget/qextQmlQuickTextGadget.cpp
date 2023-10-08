#include <qextQmlQuickTextGadget.h>
#include <qextQmlQuickTextGadget_p.h>

QEXTQmlQuickTextGadgetPrivate::QEXTQmlQuickTextGadgetPrivate(QEXTQmlQuickTextGadget *q)
    : q_ptr(q)
{
    m_text = "";
    m_color = Qt::black;
    m_scale = 1;
    m_font = QFont();
    m_fontSize = 12;
}

QEXTQmlQuickTextGadgetPrivate::~QEXTQmlQuickTextGadgetPrivate()
{

}



QEXTQmlQuickTextGadget::QEXTQmlQuickTextGadget(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QEXTQmlQuickTextGadgetPrivate(this))
{

}

QEXTQmlQuickTextGadget::~QEXTQmlQuickTextGadget()
{

}

QString QEXTQmlQuickTextGadget::text() const
{
    Q_D(const QEXTQmlQuickTextGadget);
    return d->m_text;
}

QColor QEXTQmlQuickTextGadget::color() const
{
    Q_D(const QEXTQmlQuickTextGadget);
    return d->m_color;
}

qreal QEXTQmlQuickTextGadget::scale() const
{
    Q_D(const QEXTQmlQuickTextGadget);
    return d->m_scale;
}

QFont QEXTQmlQuickTextGadget::font() const
{
    Q_D(const QEXTQmlQuickTextGadget);
    return d->m_font;
}

int QEXTQmlQuickTextGadget::fontSize() const
{
    Q_D(const QEXTQmlQuickTextGadget);
    return d->m_fontSize;
}

void QEXTQmlQuickTextGadget::setFontSize(const int &size)
{
    Q_D(QEXTQmlQuickTextGadget);
    if (size != d->m_fontSize) {
        d->m_fontSize = size;
        emit this->fontSizeChanged(size);
    }
}

void QEXTQmlQuickTextGadget::setText(const QString &text)
{
    Q_D(QEXTQmlQuickTextGadget);
    if (text != d->m_text) {
        d->m_text = text;
        emit this->textChanged();
    }
}

void QEXTQmlQuickTextGadget::setColor(const QColor &color)
{
    Q_D(QEXTQmlQuickTextGadget);
    if (color != d->m_color) {
        d->m_color = color;
        emit this->colorChanged();
    }
}

void QEXTQmlQuickTextGadget::setScale(const qreal &scale)
{
    Q_D(QEXTQmlQuickTextGadget);
    if (!qFuzzyCompare(d->m_scale, scale)) {
        d->m_scale = scale;
        emit this->scaleChanged();
    }
}

void QEXTQmlQuickTextGadget::setFont(const QFont &font)
{
    Q_D(QEXTQmlQuickTextGadget);
    if (font != d->m_font) {
        d->m_font = font;
        emit this->fontChanged();
    }
}
