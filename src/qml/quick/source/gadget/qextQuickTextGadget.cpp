#include <qextQuickTextGadget.h>
#include <qextQuickTextGadget_p.h>

QEXTQuickTextGadgetPrivate::QEXTQuickTextGadgetPrivate(QEXTQuickTextGadget *q)
    : q_ptr(q)
{
    m_text = "";
    m_color = Qt::black;
    m_scale = 1;
    m_font = QFont();
    m_fontSize = 12;
}

QEXTQuickTextGadgetPrivate::~QEXTQuickTextGadgetPrivate()
{

}



QEXTQuickTextGadget::QEXTQuickTextGadget(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QEXTQuickTextGadgetPrivate(this))
{

}

QEXTQuickTextGadget::~QEXTQuickTextGadget()
{

}

QString QEXTQuickTextGadget::text() const
{
    Q_D(const QEXTQuickTextGadget);
    return d->m_text;
}

QColor QEXTQuickTextGadget::color() const
{
    Q_D(const QEXTQuickTextGadget);
    return d->m_color;
}

qreal QEXTQuickTextGadget::scale() const
{
    Q_D(const QEXTQuickTextGadget);
    return d->m_scale;
}

QFont QEXTQuickTextGadget::font() const
{
    Q_D(const QEXTQuickTextGadget);
    return d->m_font;
}

int QEXTQuickTextGadget::fontSize() const
{
    Q_D(const QEXTQuickTextGadget);
    return d->m_fontSize;
}

void QEXTQuickTextGadget::setFontSize(const int &size)
{
    Q_D(QEXTQuickTextGadget);
    if (size != d->m_fontSize) {
        d->m_fontSize = size;
        emit this->fontSizeChanged(size);
    }
}

void QEXTQuickTextGadget::setText(const QString &text)
{
    Q_D(QEXTQuickTextGadget);
    if (text != d->m_text) {
        d->m_text = text;
        emit this->textChanged();
    }
}

void QEXTQuickTextGadget::setColor(const QColor &color)
{
    Q_D(QEXTQuickTextGadget);
    if (color != d->m_color) {
        d->m_color = color;
        emit this->colorChanged();
    }
}

void QEXTQuickTextGadget::setScale(const qreal &scale)
{
    Q_D(QEXTQuickTextGadget);
    if (!qFuzzyCompare(d->m_scale, scale)) {
        d->m_scale = scale;
        emit this->scaleChanged();
    }
}

void QEXTQuickTextGadget::setFont(const QFont &font)
{
    Q_D(QEXTQuickTextGadget);
    if (font != d->m_font) {
        d->m_font = font;
        emit this->fontChanged();
    }
}
