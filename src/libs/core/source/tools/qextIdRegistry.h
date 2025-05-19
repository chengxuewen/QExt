#ifndef _QEXTIDREGISTRY_H
#define _QEXTIDREGISTRY_H

#include <QObject>

#include <qextGlobal.h>

class QExtIdRegistryPrivate;
class QEXT_CORE_API QExtIdRegistry : public QObject
{
    Q_OBJECT
public:
    explicit QExtIdRegistry(QObject *parent = QEXT_NULLPTR);
    ~QExtIdRegistry() QEXT_OVERRIDE;

    qint64 registerdIdCount() const;

    bool isIdRegisterd(qint64 id) const;
    qint64 requestId(QObject *obj = QEXT_NULLPTR);

    void registerId(qint64 id);
    void unregisterId(qint64 id);
    void registerObjectWithId(QObject *obj, qint64 id);

protected Q_SLOTS:
    void onRequestIdObjectDestroyed(QObject *obj);

protected:
    QScopedPointer<QExtIdRegistryPrivate> dd_ptr;

private:
    Q_DISABLE_COPY(QExtIdRegistry)
    Q_DECLARE_PRIVATE_D(dd_ptr, QExtIdRegistry)
};

#endif // _QEXTIDREGISTRY_H
