#ifndef QTKEABLACKLIST_H
#define QTKEABLACKLIST_H

#include <QTKPluginFramework/QTKServiceReference>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

template<class Impl>
struct QTKEABlackList
{
    void add(const QTKServiceReference &serviceRef) {
        static_cast<Impl*>(this)->add(serviceRef);
    }

    bool contains(const QTKServiceReference &serviceRef) const {
        return static_cast<const Impl*>(this)->contains(serviceRef);
    }

    virtual ~QTKEABlackList() {}
};

#endif // QTKEABLACKLIST_H
