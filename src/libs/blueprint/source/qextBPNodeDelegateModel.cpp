#include <private/qextBPNodeDelegateModel_p.h>
#include <qextBPStyleCollection.h>

QExtBPNodeDelegateModelPrivate::QExtBPNodeDelegateModelPrivate(QExtBPNodeDelegateModel *q)
    : q_ptr(q)
    , m_nodeStyle(QExtBPStyleCollection::nodeStyle())
{
}

QExtBPNodeDelegateModelPrivate::~QExtBPNodeDelegateModelPrivate()
{
}

QExtBPNodeDelegateModel::QExtBPNodeDelegateModel(QObject *parent)
    : dd_ptr(new QExtBPNodeDelegateModelPrivate(this))
{
    // Derived classes can initialize specific style here
}

QExtBPNodeDelegateModel::~QExtBPNodeDelegateModel()
{
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
    switch (portType)
    {
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
    Q_D(const QExtBPNodeDelegateModel);
    return d->m_nodeStyle;
}

void QExtBPNodeDelegateModel::setNodeStyle(const QExtBPNodeStyle &style)
{
    Q_D(QExtBPNodeDelegateModel);
    d->m_nodeStyle = style;
}
