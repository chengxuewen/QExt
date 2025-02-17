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
    unsigned int nPorts(const QExtBPTypes::PortTypeEnum portType) const override { return 2; }

    QExtBPNodeDataType dataType(const QExtBPTypes::PortTypeEnum portType, const QExtBPTypes::PortIndex portIndex) const override
    {
        return SimpleNodeData().type();
    }

    QExtSharedPointer<QExtBPNodeData> outData(const QExtBPTypes::PortIndex port) override
    {
        return QExtSharedPointer<QExtBPNodeData>(new SimpleNodeData);
    }

    void setInData(QExtSharedPointer<QExtBPNodeData>, const QExtBPTypes::PortIndex) override {}

    QWidget *embeddedWidget() override { return QEXT_NULLPTR; }
};
