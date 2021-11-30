#ifndef _QEXTQUICK_H
#define _QEXTQUICK_H

#include <qextQuickGlobal.h>

#include <QQmlEngine>
#include <QQuickWindow>
#include <QScopedPointer>
#include <QObject>

class QEXTQuickWorld;
class QEXTQuickPrivate;
class QEXT_QUICK_API QEXTQuick : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QEXTQuick)
    Q_DECLARE_PRIVATE_D(dd_ptr, QEXTQuick)

public:
    static QObject *qmlSingletonTypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine);
    static QEXTQuick *instance();
    ~QEXTQuick();

    Q_INVOKABLE QString version() const;

    Q_INVOKABLE QString stateToString(int state) const;
    Q_INVOKABLE int stateToEnum(const QString &state) const;

    void registerTypes(const char *uri);
    void initQmlEngine(QQmlEngine *engine, const char *uri);
    void initQuickRoot(QQuickWindow *rootWindow);
    void initWorld(QEXTQuickWorld *world);

    Q_INVOKABLE int mouseAreaCursorShape() const;
    void setMouseAreaCursorShape(const Qt::CursorShape &cursor);

protected:
    explicit QEXTQuick(QObject *parent = QEXT_DECL_NULLPTR);

    QScopedPointer<QEXTQuickPrivate> dd_ptr;
};

#endif // _QEXTQUICK_H
