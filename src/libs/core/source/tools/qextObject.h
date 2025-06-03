#ifndef _QEXTOBJECT_H
#define _QEXTOBJECT_H

#include <qextGlobal.h>

#include <QObject>

class QEXT_CORE_API QExtObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject *parent READ parent WRITE setParent NOTIFY parentChanged)
public:
    explicit QExtObject(QObject *parent = nullptr);
    ~QExtObject() override;

    void setParent(QObject *parent);

Q_SIGNALS:
    void parentChanged(QObject *parent);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    QEXT_DISABLE_COPY_MOVE(QExtObject)
};

#endif // _QEXTOBJECT_H
