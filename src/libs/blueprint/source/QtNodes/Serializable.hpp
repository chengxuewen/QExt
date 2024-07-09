#pragma once

#include <QtCore/QJsonObject>

class QExtBPSerializable
{
public:
    virtual ~QExtBPSerializable() = default;

    virtual QJsonObject save() const { return {}; }

    virtual void load(QJsonObject const & /*p*/) {}
};
