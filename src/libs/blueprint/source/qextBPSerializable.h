#ifndef _QEXTBPSERIALIZABLE_H
#define _QEXTBPSERIALIZABLE_H

#include <QtCore/QJsonObject>

class QExtBPSerializable
{
public:
    virtual ~QExtBPSerializable() = default;

    virtual QJsonObject save() const { return {}; }

    virtual void load(QJsonObject const & /*p*/) {}
};

#endif // _QEXTBPSERIALIZABLE_H
