#include <qexttextgadget.h>
#include <qexttextgadget_p.h>



QEXTTextGadgetPrivate::QEXTTextGadgetPrivate(QEXTTextGadget *qq)
    : QEXTObjectPrivate(qq)
{
    m_text = "";
    m_color = Qt::black;
    m_scale = 1;
    m_font = QFont();
    m_fontSize = 12;
}

QEXTTextGadgetPrivate::~QEXTTextGadgetPrivate()
{

}



QEXTTextGadget::QEXTTextGadget(QObject *parent)
    : QObject(parent), QEXTObject(*(new QEXTTextGadgetPrivate(this)))
{

}

QEXTTextGadget::~QEXTTextGadget()
{

}

QString QEXTTextGadget::text() const
{
    QEXT_DECL_DC(QEXTTextGadget);
    return d->m_text;
}

QColor QEXTTextGadget::color() const
{
    QEXT_DECL_DC(QEXTTextGadget);
    return d->m_color;
}

qreal QEXTTextGadget::scale() const
{
    QEXT_DECL_DC(QEXTTextGadget);
    return d->m_scale;
}

QFont QEXTTextGadget::font() const
{
    QEXT_DECL_DC(QEXTTextGadget);
    return d->m_font;
}

int QEXTTextGadget::fontSize() const
{
    QEXT_DECL_DC(QEXTTextGadget);
    return d->m_fontSize;
}

void QEXTTextGadget::setFontSize(const int &size)
{
    QEXT_DECL_D(QEXTTextGadget);
    if (size != d->m_fontSize) {
        d->m_fontSize = size;
        emit this->fontSizeChanged(size);
    }
}

void QEXTTextGadget::setText(const QString &text)
{
    QEXT_DECL_D(QEXTTextGadget);
    if (text != d->m_text) {
        d->m_text = text;
        emit this->textChanged();
    }
}

void QEXTTextGadget::setColor(const QColor &color)
{
    QEXT_DECL_D(QEXTTextGadget);
    if (color != d->m_color) {
        d->m_color = color;
        emit this->colorChanged();
    }
}

void QEXTTextGadget::setScale(const qreal &scale)
{
    QEXT_DECL_D(QEXTTextGadget);
    if (!qFuzzyCompare(d->m_scale, scale)) {
        d->m_scale = scale;
        emit this->scaleChanged();
    }
}

void QEXTTextGadget::setFont(const QFont &font)
{
    QEXT_DECL_D(QEXTTextGadget);
    if (font != d->m_font) {
        d->m_font = font;
        emit this->fontChanged();
    }
}
