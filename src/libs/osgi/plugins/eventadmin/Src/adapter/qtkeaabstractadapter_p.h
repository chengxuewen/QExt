#ifndef QTKEAABSTRACTADAPTER_P_H
#define QTKEAABSTRACTADAPTER_P_H

#include <QTKPluginFramework/Service/Event/QTKEventAdmin>
#include <QTKPluginFramework/QTKPluginContext>

#include <QAtomicPointer>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKEAAbstractAdapter
{
public:
    QTKEAAbstractAdapter(QTKEventAdmin *pAdmin);
    virtual ~QTKEAAbstractAdapter() {}

    virtual void destroy(QTKPluginContext *pPluginContext) = 0;

protected:
    QTKEventAdmin* getEventAdmin() const;

private:
    mutable QAtomicPointer<QTKEventAdmin> m_admin;
};

#endif // QTKEAABSTRACTADAPTER_P_H
