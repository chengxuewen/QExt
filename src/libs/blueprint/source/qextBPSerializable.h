#ifndef _QEXTBPSERIALIZABLE_H
#define _QEXTBPSERIALIZABLE_H

#include <QtCore/QJsonObject>

class QExtBPSerializable
{
public:
    virtual ~QExtBPSerializable() {}

    virtual QJsonObject save() const { return QJsonObject(); }

    virtual void load(const QJsonObject & /*p*/) {}
};

#endif // _QEXTBPSERIALIZABLE_H
