#ifndef _QEXTJSON_H
#define _QEXTJSON_H

#include <qextGlobal.h>

class QExtJson : public QObject
{
    Q_OBJECT
public:
    explicit QExtJson(QObject *parent = QEXT_NULLPTR);

signals:
};

class QExtJsonDocumentPrivate;
class QEXT_CORE_API QExtJsonDocument
{
public:
    QExtJsonDocument();
    virtual ~QExtJsonDocument();


protected:
    QScopedPointer<QExtJsonDocumentPrivate> dd_ptr;

private:
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtJsonDocument)
    QEXT_DISABLE_COPY_MOVE(QExtJsonDocument)
};

#endif // _QEXTJSON_H
