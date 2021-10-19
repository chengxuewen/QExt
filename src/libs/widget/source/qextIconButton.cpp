#include <qextIconButton.h>
#include <qextIconButton_p.h>

//#include <lib/qtmaterialstyle.h"
//#include <lib/qtmaterialrippleoverlay.h"

#include <QPainter>
#include <QEvent>
#include <QStyleOption>

QEXTIconButtonPrivate::QEXTIconButtonPrivate(QEXTIconButton *q)
    : q_ptr(q)
{
}

QEXTIconButtonPrivate::~QEXTIconButtonPrivate()
{
}

void QEXTIconButtonPrivate::init()
{
    Q_Q(QEXTIconButton);

    //    rippleOverlay  = new QtMaterialRippleOverlay(q->parentWidget());
    m_useThemeColors = true;

    //    rippleOverlay->installEventFilter(q);
    //    q->setStyle(&QtMaterialStyle::instance());

    //    QSizePolicy policy;
    //    policy.setWidthForHeight(true);
    //    q->setSizePolicy(policy);
}

void QEXTIconButtonPrivate::updateRipple()
{
    Q_Q(QEXTIconButton);

    //    QRect r(q->rect());
    //    r.setSize(QSize(q->width() * 2, q->height() * 2));
    //    r.moveCenter(q->geometry().center());
    //    rippleOverlay->setGeometry(r);
}

/*!
 *  \class QEXTIconButton
 */

QEXTIconButton::QEXTIconButton(const QIcon &icon, QWidget *parent)
    : QAbstractButton(parent), d_ptr(new QEXTIconButtonPrivate(this))
{
    d_func()->init();
    this->setIcon(icon);
}

QEXTIconButton::QEXTIconButton(QWidget *parent)
    : QAbstractButton(parent), d_ptr(new QEXTIconButtonPrivate(this))
{
    d_func()->init();
}

QEXTIconButton::~QEXTIconButton()
{
}

/*!
 *  \reimp
 */
QSize QEXTIconButton::sizeHint() const
{
    return this->iconSize();
}

void QEXTIconButton::setBackgroundColor(const QColor &color)
{
    Q_D(QEXTIconButton);

    d->m_backgroundColor = color;

    //    MATERIAL_DISABLE_THEME_COLORS
    this->update();
}

QColor QEXTIconButton::backgroundColor() const
{
    Q_D(const QEXTIconButton);

    //    if (d->useThemeColors || !d->color.isValid())
    //    {
    //        return QtMaterialStyle::instance().themeColor("text");
    //    }
    return d->m_backgroundColor;
}

//void QEXTIconButton::setUseThemeColors(bool value)
//{
//    Q_D(QEXTIconButton);

//    if (d->m_useThemeColors == value)
//    {
//        return;
//    }

//    d->m_useThemeColors = value;
//    this->update();
//}

//bool QEXTIconButton::useThemeColors() const
//{
//    Q_D(const QEXTIconButton);

//    return d->m_useThemeColors;
//}

void QEXTIconButton::setIconColor(const QColor &color)
{
    Q_D(QEXTIconButton);

    d->m_iconColor = color;

    //    MATERIAL_DISABLE_THEME_COLORS
    this->update();
}

QColor QEXTIconButton::iconColor() const
{
    Q_D(const QEXTIconButton);

    //    if (d->useThemeColors || !d->color.isValid())
    //    {
    //        return QtMaterialStyle::instance().themeColor("text");
    //    }
    return d->m_iconColor;
}

void QEXTIconButton::setDisabledColor(const QColor &color)
{
    Q_D(QEXTIconButton);

    d->m_disabledColor = color;

    //    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QEXTIconButton::disabledColor() const
{
    Q_D(const QEXTIconButton);

    //    if (d->useThemeColors || !d->disabledColor.isValid())
    //    {
    //        return QtMaterialStyle::instance().themeColor("disabled");
    //    }
    return d->m_disabledColor;
}

QEXTIconButton::QEXTIconButton(QEXTIconButtonPrivate &d, QWidget *parent)
    : QAbstractButton(parent),
      d_ptr(&d)
{
    d_func()->init();
}

/*!
 *  \reimp
 */
bool QEXTIconButton::event(QEvent *event)
{
    Q_D(QEXTIconButton);

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
bool QEXTIconButton::eventFilter(QObject *obj, QEvent *event)
{
    if (QEvent::Resize == event->type())
    {
        Q_D(QEXTIconButton);

        //        d->updateRipple();
    }
    return QAbstractButton::eventFilter(obj, event);
}

/*!
 *  \reimp
 */
void QEXTIconButton::mousePressEvent(QMouseEvent *event)
{
    Q_D(QEXTIconButton);

    //    d->rippleOverlay->addRipple(QPoint(d->rippleOverlay->width(), d->rippleOverlay->height()) / 2, iconSize().width());
    emit clicked();

    QAbstractButton::mousePressEvent(event);
}

/*!
 *  \reimp
 */
void QEXTIconButton::paintEvent(QPaintEvent *event)
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

    QRect r(rect());
    const qreal w = pixmap.width();
    const qreal h = pixmap.height();
    painter.drawPixmap(QRect((r.width() - w) / 2, (r.height() - h) / 2, w, h), pixmap);
}
