#include <private/qextQuickTextGadget_p.h>

QExtQuickTextGadgetPrivate::QExtQuickTextGadgetPrivate(QExtQuickTextGadget *q)
    : q_ptr(q)
{
    m_text = "";
    m_color = Qt::black;
    m_scale = 1;
    m_font = QFont();
    m_fontSize = 12;
}

QExtQuickTextGadgetPrivate::~QExtQuickTextGadgetPrivate()
{

}



QExtQuickTextGadget::QExtQuickTextGadget(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtQuickTextGadgetPrivate(this))
{

}

QExtQuickTextGadget::~QExtQuickTextGadget()
{

}

QString QExtQuickTextGadget::text() const
{
    Q_D(const QExtQuickTextGadget);
    return d->m_text;
}

QColor QExtQuickTextGadget::color() const
{
    Q_D(const QExtQuickTextGadget);
    return d->m_color;
}

qreal QExtQuickTextGadget::scale() const
{
    Q_D(const QExtQuickTextGadget);
    return d->m_scale;
}

QFont QExtQuickTextGadget::font() const
{
    Q_D(const QExtQuickTextGadget);
    return d->m_font;
}

int QExtQuickTextGadget::fontSize() const
{
    Q_D(const QExtQuickTextGadget);
    return d->m_fontSize;
}

void QExtQuickTextGadget::setFontSize(const int &size)
{
    Q_D(QExtQuickTextGadget);
    if (size != d->m_fontSize) {
        d->m_fontSize = size;
        emit this->fontSizeChanged(size);
    }
}

void QExtQuickTextGadget::setText(const QString &text)
{
    Q_D(QExtQuickTextGadget);
    if (text != d->m_text) {
        d->m_text = text;
        emit this->textChanged();
    }
}

void QExtQuickTextGadget::setColor(const QColor &color)
{
    Q_D(QExtQuickTextGadget);
    if (color != d->m_color) {
        d->m_color = color;
        emit this->colorChanged();
    }
}

void QExtQuickTextGadget::setScale(const qreal &scale)
{
    Q_D(QExtQuickTextGadget);
    if (!qFuzzyCompare(d->m_scale, scale)) {
        d->m_scale = scale;
        emit this->scaleChanged();
    }
}

void QExtQuickTextGadget::setFont(const QFont &font)
{
    Q_D(QExtQuickTextGadget);
    if (font != d->m_font) {
        d->m_font = font;
        emit this->fontChanged();
    }
}
