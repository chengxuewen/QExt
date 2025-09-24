#ifndef _QEXTQMLREGISTRATION_H
#define _QEXTQMLREGISTRATION_H

#include <QQmlEngine>

#if (QT_VERSION >= QT_VERSION_CHECK(6, 2, 0))
#   include <QtQml/qqmlregistration.h>
#   define QEXT_QML_ELEMENT() QML_ELEMENT
#   define QEXT_QML_SINGLETON() QML_SINGLETON
#   define QEXT_QML_SINGLETON_TYPE(type) type
#   define QEXT_QML_DECLARE_REGISTRATION(URI) \
    extern void qml_register_types_##URI(); \
    Q_GHS_KEEP_REFERENCE(qml_register_types_##URI)
#else
#   define QEXT_QML_ELEMENT()
#   define QEXT_QML_SINGLETON()
#   define QEXT_QML_SINGLETON_TYPE(type) QObject
#   define QEXT_QML_DECLARE_REGISTRATION(URI) static void qml_register_types_##URI() {}
#endif
#define QEXT_QML_REFERENCE_REGISTRATION(URI) \
    volatile auto registration = &qml_register_types_##URI; \
    Q_UNUSED(registration)

#endif // _QEXTQMLREGISTRATION_H
