#ifndef _QEXTQMLSINGLETON_H
#define _QEXTQMLSINGLETON_H

#include <qextQmlRegistration.h>
#include <qextSingleton.h>

#include <QQmlEngine>

template <typename T>
class QExtQmlSingleton : public QExtSingleton<T>
{
public:
    Q_INVOKABLE virtual QString version() const { return ""; }

protected:
    virtual void onQmlCreated(QQmlEngine */*engine*/, QJSEngine */*scriptEngine*/) { }
};

template <typename T>
class QExtQmlObjectSingleton : public QObject, public QExtQmlSingleton<T>
{
    QEXT_DECLARE_OBJECT_SINGLETON()
};

template <typename T>
class QExtQmlModuleSingleton : public QExtQmlObjectSingleton<T>
{
public:
    virtual void registerTypes(const char *uri = nullptr) = 0;
    virtual void initializeEngine(QQmlEngine *engine, const char *uri) = 0;
};

#define QEXT_DECLARE_QML_SINGLETON(CLASS) \
    public: \
    static QEXT_QML_SINGLETON_TYPE(CLASS) *create(QQmlEngine *engine, QJSEngine *scriptEngine) { \
        QQmlEngine::setObjectOwnership(CLASS::instance(), QQmlEngine::CppOwnership); \
        CLASS::instance()->onQmlCreated(engine, scriptEngine); \
        return CLASS::instance(); \
    } \
    private: \
    Q_PROPERTY(QString version READ version CONSTANT FINAL) \
    QEXT_DECLARE_OBJECT_SINGLETON() \
    QEXT_DECLARE_SINGLETON(CLASS) \
    QEXT_QML_SINGLETON() \
    QEXT_QML_ELEMENT()

#endif // _QEXTQMLSINGLETON_H
