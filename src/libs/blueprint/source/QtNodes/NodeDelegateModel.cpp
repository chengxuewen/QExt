#include "NodeDelegateModel.hpp"

#include "StyleCollection.hpp"

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

void QExtBPNodeDelegateModel::load(QJsonObject const &)
{
    //
}

QExtBPTypes::ConnectionPolicyEnum QExtBPNodeDelegateModel::portConnectionPolicy(QExtBPTypes::PortTypeEnum portType, QExtBPTypes::PortIndex) const
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

QExtBPNodeStyle const &QExtBPNodeDelegateModel::nodeStyle() const
{
    return _nodeStyle;
}

void QExtBPNodeDelegateModel::setNodeStyle(QExtBPNodeStyle const &style)
{
    _nodeStyle = style;
}

