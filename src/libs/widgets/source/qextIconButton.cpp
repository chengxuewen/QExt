/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2022~Present ChengXueWen. Contact: 1398831004@qq.com
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
** documentation files (the "Software"), to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
** and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all copies or substantial portions
** of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
** CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
** IN THE SOFTWARE.
**
***********************************************************************************************************************/

#include <private/qextIconButton_p.h>

//#include <lib/qtmaterialstyle.h"
//#include <lib/qtmaterialrippleoverlay.h"

#include <QPainter>
#include <QEvent>
#include <QStyleOption>

QExtIconButtonPrivate::QExtIconButtonPrivate(QExtIconButton *q)
    : q_ptr(q)
{
}

QExtIconButtonPrivate::~QExtIconButtonPrivate()
{
}

void QExtIconButtonPrivate::init()
{
    Q_Q(QExtIconButton);

    //    rippleOverlay  = new QtMaterialRippleOverlay(q->parentWidget());
    m_useThemeColors = true;

    //    rippleOverlay->installEventFilter(q);
    //    q->setStyle(&QtMaterialStyle::instance());

    //    QSizePolicy policy;
    //    policy.setWidthForHeight(true);
    //    q->setSizePolicy(policy);
}

void QExtIconButtonPrivate::updateRipple()
{
    Q_Q(QExtIconButton);

    //    QRect r(q->rect());
    //    r.setSize(QSize(q->width() * 2, q->height() * 2));
    //    r.moveCenter(q->geometry().center());
    //    rippleOverlay->setGeometry(r);
}

/*!
 *  \class QExtIconButton
 */

QExtIconButton::QExtIconButton(const QIcon &icon, QWidget *parent)
    : QPushButton(parent), dd_ptr(new QExtIconButtonPrivate(this))
{
    d_func()->init();
    this->setIcon(icon);
}

QExtIconButton::QExtIconButton(QWidget *parent)
    : QPushButton(parent), dd_ptr(new QExtIconButtonPrivate(this))
{
    d_func()->init();
}

QExtIconButton::~QExtIconButton()
{
}

/*!
 *  \reimp
 */
QSize QExtIconButton::sizeHint() const
{
    return this->iconSize();
}

void QExtIconButton::setBackgroundColor(const QColor &color)
{
    Q_D(QExtIconButton);

    d->m_backgroundColor = color;

    //    MATERIAL_DISABLE_THEME_COLORS
    this->update();
}

QColor QExtIconButton::backgroundColor() const
{
    Q_D(const QExtIconButton);

    //    if (d->useThemeColors || !d->color.isValid())
    //    {
    //        return QtMaterialStyle::instance().themeColor("text");
    //    }
    return d->m_backgroundColor;
}

//void QExtIconButton::setUseThemeColors(bool value)
//{
//    Q_D(QExtIconButton);

//    if (d->m_useThemeColors == value)
//    {
//        return;
//    }

//    d->m_useThemeColors = value;
//    this->update();
//}

//bool QExtIconButton::useThemeColors() const
//{
//    Q_D(const QExtIconButton);

//    return d->m_useThemeColors;
//}

void QExtIconButton::setIconColor(const QColor &color)
{
    Q_D(QExtIconButton);

    d->m_iconColor = color;

    //    MATERIAL_DISABLE_THEME_COLORS
    this->update();
}

QColor QExtIconButton::iconColor() const
{
    Q_D(const QExtIconButton);

    //    if (d->useThemeColors || !d->color.isValid())
    //    {
    //        return QtMaterialStyle::instance().themeColor("text");
    //    }
    return d->m_iconColor;
}

void QExtIconButton::setDisabledColor(const QColor &color)
{
    Q_D(QExtIconButton);

    d->m_disabledColor = color;

    //    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QExtIconButton::disabledColor() const
{
    Q_D(const QExtIconButton);

    //    if (d->useThemeColors || !d->disabledColor.isValid())
    //    {
    //        return QtMaterialStyle::instance().themeColor("disabled");
    //    }
    return d->m_disabledColor;
}

void QExtIconButton::rotateIcon()
{

}

QExtIconButton::QExtIconButton(QExtIconButtonPrivate &d, QWidget *parent)
    : QPushButton(parent),
      dd_ptr(&d)
{
    d_func()->init();
}

bool QExtIconButton::event(QEvent *event)
{
    Q_D(QExtIconButton);

    switch (event->type())
    {
    case QEvent::Move:
    case QEvent::Resize:
        d->updateRipple();
        break;
    case QEvent::ParentChange:
    {
        QWidget *widget;
        if ((widget = parentWidget()))
        {
            //                    d->rippleOverlay->setParent(widget);
        }
        break;
    }
    default:
        break;
    }
    return QAbstractButton::event(event);
}

/*!
 *  \reimp
 */
bool QExtIconButton::eventFilter(QObject *obj, QEvent *event)
{
    if (QEvent::Resize == event->type())
    {
        Q_D(QExtIconButton);

        //        d->updateRipple();
    }
    return QAbstractButton::eventFilter(obj, event);
}

/*!
 *  \reimp
 */
void QExtIconButton::mousePressEvent(QMouseEvent *event)
{
    Q_D(QExtIconButton);
    emit this->clicked();
    QAbstractButton::mousePressEvent(event);
}

void QExtIconButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);

    QStyleOption opt;
    opt.init(this);
    this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    //    painter.save();
    //    painter.setBrush(Qt::gray);
    //    painter.drawRect(this->rect());
    //    painter.restore();

    QPixmap pixmap = icon().pixmap(iconSize());
    QPainter iconPainter(&pixmap);
    iconPainter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    iconPainter.fillRect(pixmap.rect(), isEnabled() ? iconColor() : disabledColor());

    QRect rect(this->rect());
    const qreal w = pixmap.width();
    const qreal h = pixmap.height();
    painter.drawPixmap(QRect((rect.width() - w) / 2, (rect.height() - h) / 2, w, h), pixmap);
}
