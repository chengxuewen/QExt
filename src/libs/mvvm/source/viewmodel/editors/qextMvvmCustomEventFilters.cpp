#include <qextMvvmCustomEventFilters.h>

#include <QEvent>
#include <QComboBox>
#include <QAbstractSpinBox>

QEXTMvvmLostFocusFilter::QEXTMvvmLostFocusFilter(QObject *parent)
    : QObject(parent)
{

}

QEXTMvvmLostFocusFilter::~QEXTMvvmLostFocusFilter()
{

}

bool QEXTMvvmLostFocusFilter::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusOut)
    {
        return true;
    }

    return QObject::eventFilter(obj, event);
}

QEXTMvvmWheelEventFilter::QEXTMvvmWheelEventFilter(QObject *parent)
    : QObject(parent)
{

}

QEXTMvvmWheelEventFilter::~QEXTMvvmWheelEventFilter()
{

}

bool QEXTMvvmWheelEventFilter::eventFilter(QObject *obj, QEvent *event)
{
    QAbstractSpinBox *spinBox = qobject_cast<QAbstractSpinBox *>(obj);
    QComboBox *comboBox = qobject_cast<QComboBox *>(obj);
    if (spinBox)
    {
        if (event->type() == QEvent::Wheel)
        {
            if (spinBox->focusPolicy() == Qt::WheelFocus)
            {
                event->accept();
                return false;
            }
            else
            {
                event->ignore();
                return true;
            }
        }
        else if (event->type() == QEvent::FocusIn)
        {
            spinBox->setFocusPolicy(Qt::WheelFocus);
        }
        else if (event->type() == QEvent::FocusOut)
        {
            spinBox->setFocusPolicy(Qt::StrongFocus);
        }
    }
    else if (comboBox)
    {
        if (event->type() == QEvent::Wheel)
        {
            event->ignore();
            return true;
        }
        else
        {
            event->accept();
            return false;
        }
    }
    return QObject::eventFilter(obj, event);
}
