#include "qtkeaabstractadapter_p.h"

#include <QTKCore/QTKException>

QTK_CORE_USE_NAMESPACE

QTKEAAbstractAdapter::QTKEAAbstractAdapter(QTKEventAdmin *pAdmin)
    : m_admin(0)
{
    if (nullptr == pAdmin) {
        throw QTKInvalidArgumentException("EventAdmin must not be null");
    }
    m_admin.testAndSetOrdered(0, pAdmin);
}

QTKEventAdmin *QTKEAAbstractAdapter::getEventAdmin() const
{
    return m_admin.fetchAndAddOrdered(0);
}
