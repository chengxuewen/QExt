#include <qextMessageBox.h>
#include <qextSpinlock.h>

#include <QHash>
#include <QIcon>
#include <QGlobalStatic>
#include <QDialogButtonBox>

typedef QVector<QIcon> IconVector;
namespace detail
{
Q_GLOBAL_STATIC_WITH_ARGS(QSize, sgCustomIconSize, (50, 50))
Q_GLOBAL_STATIC(QExtSpinLock, sgCustomIconSizeSpinlock)
Q_GLOBAL_STATIC_WITH_ARGS(IconVector, sgCustomIcons, (8))
Q_GLOBAL_STATIC(QExtSpinLock, sgCustomIconsSpinlock)
static const QSize &customIconSize()
{
    QExtSpinLock::Locker locker(*sgCustomIconSizeSpinlock);
    return *sgCustomIconSize;
}
static void setCustomIconSize(const QSize &size)
{
    QExtSpinLock::Locker locker(*sgCustomIconSizeSpinlock);
    *sgCustomIconSize = size;
}
static const QIcon &customIcon(int index)
{
    QExtSpinLock::Locker locker(*sgCustomIconsSpinlock);
    return sgCustomIcons->at(index);
}
static void setCustomIcon(int index, const QIcon &icon)
{
    QExtSpinLock::Locker locker(*sgCustomIconsSpinlock);
    sgCustomIcons->replace(index, icon);
}
static QMessageBox::StandardButton showMessageBox(QWidget *parent,
                                                  QMessageBox::Icon icon,
                                                  const QString& title, const QString& text,
                                                  QMessageBox::StandardButtons buttons,
                                                  QMessageBox::StandardButton defaultButton)
{
    QMessageBox messageBox(icon, title, text, QMessageBox::NoButton, parent);
    const QIcon &iconResource = detail::customIcon(icon);
    if (!iconResource.isNull())
    {
        messageBox.setIconPixmap(iconResource.pixmap(detail::customIconSize()));
    }
    QDialogButtonBox *buttonBox = messageBox.findChild<QDialogButtonBox*>();
    Q_ASSERT(QEXT_NULLPTR != buttonBox);
    uint mask = QMessageBox::FirstButton;
    while (mask <= QMessageBox::LastButton)
    {
        uint sb = buttons & mask;
        mask <<= 1;
        if (!sb)
        {
            continue;
        }
        QPushButton *button = messageBox.addButton((QMessageBox::StandardButton)sb);
        // Choose the first accept role as the default
        if (messageBox.defaultButton())
        {
            continue;
        }
        if ((defaultButton == QMessageBox::NoButton && buttonBox->buttonRole((QAbstractButton *)button) == QDialogButtonBox::AcceptRole)
            || (defaultButton != QMessageBox::NoButton && sb == uint(defaultButton)))
        {
            messageBox.setDefaultButton(button);
        }
    }
    if (messageBox.exec() == -1)
    {
        return QMessageBox::Cancel;
    }
    return messageBox.standardButton(messageBox.clickedButton());
}
}

QExtMessageBox::QExtMessageBox(QWidget *parent)
    : QMessageBox(parent)
{
}

QExtMessageBox::QExtMessageBox(Icon icon, const QString &title, const QString &text,
                               StandardButtons buttons, QWidget *parent, Qt::WindowFlags flags)
    : QMessageBox(icon, title, text, buttons, parent, flags)
{
}

QSize QExtMessageBox::customIconSize()
{
    return detail::customIconSize();
}

void QExtMessageBox::setCustomIconSize(const QSize &size)
{
    detail::setCustomIconSize(size);
}

const QIcon &QExtMessageBox::customIcon(Icon type)
{
    return detail::customIcon(type);
}

void QExtMessageBox::setCustomIcon(Icon type, const QIcon &icon)
{
    detail::setCustomIcon(type, icon);
}

QMessageBox::StandardButton QExtMessageBox::information(QWidget *parent, const QString &title, const QString &text,
                                                        StandardButtons buttons, StandardButton defaultButton)
{
    return detail::showMessageBox(parent, Information, title, text, buttons, defaultButton);
}

QMessageBox::StandardButton QExtMessageBox::question(QWidget *parent, const QString &title, const QString &text,
                                                     StandardButtons buttons, StandardButton defaultButton)
{
    return detail::showMessageBox(parent, Question, title, text, buttons, defaultButton);
}

QMessageBox::StandardButton QExtMessageBox::warning(QWidget *parent, const QString &title, const QString &text,
                                                    StandardButtons buttons, StandardButton defaultButton)
{
    return detail::showMessageBox(parent, Warning, title, text, buttons, defaultButton);
}

QMessageBox::StandardButton QExtMessageBox::critical(QWidget *parent, const QString &title, const QString &text,
                                                     StandardButtons buttons, StandardButton defaultButton)
{
    return detail::showMessageBox(parent, Critical, title, text, buttons, defaultButton);
}
