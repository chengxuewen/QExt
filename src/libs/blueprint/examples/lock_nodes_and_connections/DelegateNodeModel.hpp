#pragma once

#include <QtCore/QObject>

#include <QExtBlueprint>

#include <memory>

class SimpleNodeData : public QExtBPNodeData
{
public:
    QExtBPNodeDataType type() const override { return QExtBPNodeDataType{"SimpleData", "Simple Data"}; }
};

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class SimpleDataModel : public QExtBPNodeDelegateModel
{
    Q_OBJECT

public:
    QString caption() const override { return QString("Simple Data Model"); }

    QString name() const override { return QString("SimpleDataModel"); }

public:
    unsigned int nPorts(QExtBPTypes::PortTypeEnum const portType) const override { return 2; }

    QExtBPNodeDataType dataType(QExtBPTypes::PortTypeEnum const portType, QExtBPTypes::PortIndex const portIndex) const override
    {
        return SimpleNodeData().type();
    }

    std::shared_ptr<QExtBPNodeData> outData(QExtBPTypes::PortIndex const port) override
    {
        return std::make_shared<SimpleNodeData>();
    }

    void setInData(std::shared_ptr<QExtBPNodeData>, QExtBPTypes::PortIndex const) override {}

    QWidget *embeddedWidget() override { return nullptr; }
};
