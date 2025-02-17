#pragma once

#include <QtCore/QObject>

#include <QExtBlueprint>

#include <memory>


/// The class can potentially incapsulate any user data which need to
/// be transferred within the Node Editor graph
class MyNodeData : public QExtBPNodeData
{
public:
    QExtBPNodeDataType type() const override { return QExtBPNodeDataType{"MyNodeData", "My Node Data"}; }
};

//------------------------------------------------------------------------------

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class MyDataModel : public QExtBPNodeDelegateModel
{
    Q_OBJECT
public:
    ~MyDataModel() = default;

public:
    QString caption() const override { return QString("My Data Model"); }

    QString name() const override { return QString("MyDataModel"); }

public:
    QJsonObject save() const override
    {
        QJsonObject modelJson;

        modelJson["name"] = name();

        return modelJson;
    }

public:
    unsigned int nPorts(const QExtBPTypes::PortTypeEnum) const override { return 3; }

    QExtBPNodeDataType dataType(const QExtBPTypes::PortTypeEnum, const QExtBPTypes::PortIndex) const override
    {
        return MyNodeData().type();
    }

    QExtSharedPointer<QExtBPNodeData> outData(QExtBPTypes::PortIndex) override { return qextMakeShared<MyNodeData>(); }

    void setInData(QExtSharedPointer<QExtBPNodeData>, const QExtBPTypes::PortIndex) override {}

    QWidget *embeddedWidget() override { return QEXT_NULLPTR; }
};
