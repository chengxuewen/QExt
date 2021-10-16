#ifndef _QEXTSIMPLEOBJECT_H
#define _QEXTSIMPLEOBJECT_H

#include <qextObject.h>

#include <QObject>

class QEXTSimpleObjectPrivate;
class QEXTSimpleObject : public QObject, public QEXTObject
{
    Q_OBJECT
public:
    explicit QEXTSimpleObject(QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTSimpleObject();

    QString string() const;
    void setString(const QString &string);

private:
    QEXT_DECL_PRIVATE(QEXTSimpleObject)
    QEXT_DISABLE_COPY_MOVE(QEXTSimpleObject)
};

#endif // _QEXTSIMPLEOBJECT_H
