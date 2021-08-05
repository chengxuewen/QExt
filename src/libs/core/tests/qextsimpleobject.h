#ifndef QEXTSIMPLEOBJECT_H
#define QEXTSIMPLEOBJECT_H

#include <qextobject.h>

#include <QObject>



class QEXTSimpleObjectPrivate;
class QEXTSimpleObject : public QObject, public QEXTObject
{
    Q_OBJECT
public:
    explicit QEXTSimpleObject(QObject *parent = QEXT_NULLPTR);
    ~QEXTSimpleObject();

    QString string() const;
    void setString(const QString &string);

private:
    QEXT_DECLARE_PRIVATE(QEXTSimpleObject)
    QEXT_DISABLE_COPY_MOVE(QEXTSimpleObject)
};

#endif // QEXTSIMPLEOBJECT_H
