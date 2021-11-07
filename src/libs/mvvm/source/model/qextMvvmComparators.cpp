#include <QMetaType>
#include <qextMvvmComboProperty.h>
#include <qextMvvmComparators.h>
#include <qextMvvmUtils.h>
#include <qextMvvmExternalProperty.h>
#include <qextMvvmRealLimits.h>



bool QEXTMvvmComparators::m_isRegistered = false;

void QEXTMvvmComparators::registerComparators()
{
    if (!m_isRegistered) {
        QMetaType::registerComparators<QVector<double>>();
        QMetaType::registerComparators<QEXTMvvmComboProperty>();
        QMetaType::registerComparators<QEXTMvvmExternalProperty>();
        QMetaType::registerComparators<QEXTMvvmRealLimits>();
        m_isRegistered = true;
    }
}

bool QEXTMvvmComparators::registered()
{
    return m_isRegistered;
}
