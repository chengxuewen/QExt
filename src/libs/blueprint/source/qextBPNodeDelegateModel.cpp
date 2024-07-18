#include <qextBPNodeDelegateModel.h>
#include <qextBPStyleCollection.h>

QExtBPNodeDelegateModel::QExtBPNodeDelegateModel()
    : _nodeStyle(QExtBPStyleCollection::nodeStyle())
{
    // Derived classes can initialize specific style here
}

QJsonObject QExtBPNodeDelegateModel::save() const
{
    QJsonObject modelJson;

    modelJson["model-name"] = name();

    return modelJson;
}

void QExtBPNodeDelegateModel::load(const QJsonObject &)
{
    //
}

QExtBPTypes::ConnectionPolicyEnum QExtBPNodeDelegateModel::portConnectionPolicy(QExtBPTypes::PortTypeEnum portType,
                                                                                QExtBPTypes::PortIndex) const
{
    auto result = QExtBPTypes::ConnectionPolicy_One;
    switch (portType) {
    case QExtBPTypes::PortType_In:
        result = QExtBPTypes::ConnectionPolicy_One;
        break;
    case QExtBPTypes::PortType_Out:
        result = QExtBPTypes::ConnectionPolicy_Many;
        break;
    case QExtBPTypes::PortType_None:
        break;
    }

    return result;
}

const QExtBPNodeStyle &QExtBPNodeDelegateModel::nodeStyle() const
{
    return _nodeStyle;
}

void QExtBPNodeDelegateModel::setNodeStyle(const QExtBPNodeStyle &style)
{
    _nodeStyle = style;
}

