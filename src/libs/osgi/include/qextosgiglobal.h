#ifndef QEXTOSGIGLOBAL_H
#define QEXTOSGIGLOBAL_H

#include <qextglobal.h>
#include <QHash>
#include <QVariant>
#include <QStringList>
#include <QSharedPointer>

/********************************************************************************
   QEXT Compiler specific cmds for export and import code to DLL
********************************************************************************/
#ifdef QEXT_BUILD_SHARED_LIBS // compiled as a dynamic lib.
#   ifdef QEXT_BUILD_OSGI_LIB // defined if we are building the lib
#       define QEXT_OSGI_API Q_DECL_EXPORT
#   else
#       define QEXT_OSGI_API Q_DECL_IMPORT
#   endif
#   define QEXT_OSGI_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
#   define QEXT_OSGI_API
#   define QEXT_OSGI_HIDDEN
#endif


typedef QHash<QString, QVariant> QTKProperties;
typedef QTKProperties QTKDictionary;

#if QT_VERSION < 0x040700
#include <QSharedPointer>
template<class T>
inline uint qHash(const QSharedPointer<T>& ptr)
{
    return qHash<T>(ptr.data());
}
#endif

template<class A>
QStringList getIIDs()
{
    return QStringList(qobject_interface_iid<A*>());
}

template<class A, class B>
QStringList getIIDs()
{
    QStringList ids;
    ids << qobject_interface_iid<A*>();
    ids << qobject_interface_iid<B*>();
    return ids;
}

template<class A, class B, class C>
QStringList getIIDs()
{
    QStringList ids;
    ids << qobject_interface_iid<A*>();
    ids << qobject_interface_iid<B*>();
    ids << qobject_interface_iid<C*>();
    return ids;
}

template<class A, class B, class C, class D>
QStringList getIIDs()
{
    QStringList ids;
    ids << qobject_interface_iid<A*>();
    ids << qobject_interface_iid<B*>();
    ids << qobject_interface_iid<C*>();
    ids << qobject_interface_iid<D*>();
    return ids;
}

#endif // QEXTOSGIGLOBAL_H
