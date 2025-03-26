// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmCustomEventFilters.h>
#include <QAbstractSpinBox>
#include <QComboBox>
#include <QEvent>

using namespace ModelView;

QExtMvvmLostFocusFilter::QExtMvvmLostFocusFilter(QObject* parent) : QObject(parent) {}

bool QExtMvvmLostFocusFilter::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::FocusOut)
        return true;

    return QObject::eventFilter(obj, event);
}

// ----------------------------------------------------------------------------

QExtMvvmWheelEventFilter::QExtMvvmWheelEventFilter(QObject* parent) : QObject(parent) {}

bool QExtMvvmWheelEventFilter::eventFilter(QObject* obj, QEvent* event)
{
    auto spinBox = qobject_cast<QAbstractSpinBox*>(obj);
    if (spinBox)
    {
        if (event->type() == QEvent::Wheel) {
            if (spinBox->focusPolicy() == Qt::WheelFocus) {
                event->accept();
                return false;
            }
            else {
                event->ignore();
                return true;
            }
        }
        else if (event->type() == QEvent::FocusIn) {
            spinBox->setFocusPolicy(Qt::WheelFocus);
        }
        else if (event->type() == QEvent::FocusOut) {
            spinBox->setFocusPolicy(Qt::StrongFocus);
        }
    }
    else
    {
        auto comboBox = qobject_cast<QComboBox*>(obj);
        if (comboBox)
        {
            if (event->type() == QEvent::Wheel)
            {
                event->ignore();
                return true;
            }
        }
        else
        {
            event->accept();
            return false;
        }
    }
    return QObject::eventFilter(obj, event);
}
