#pragma once

#include <QExtBlueprint>

#include <QObject>

#include <memory>

//using QtNodes::QExtBPNodeData;
//using QtNodes::QExtBPNodeDataType;
//using QExtBPNodeDelegateModel;
//using QExtBPTypes::PortIndex;
//using QExtBPTypes::PortTypeEnum;

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class MyNodeData : public QExtBPNodeData
{
public:
    QExtBPNodeDataType type() const override { return QExtBPNodeDataType{"MyNodeData", "My Node Data"}; }
};

class SimpleNodeData : public QExtBPNodeData
{
public:
    QExtBPNodeDataType type() const override { return QExtBPNodeDataType{"SimpleData", "Simple Data"}; }
};

//------------------------------------------------------------------------------

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class NaiveDataModel : public QExtBPNodeDelegateModel
{
    Q_OBJECT

public:
    virtual ~NaiveDataModel() {}

public:
    QString caption() const override { return QString("Naive Data Model"); }

    QString name() const override { return QString("NaiveDataModel"); }

public:
    unsigned int nPorts(const QExtBPTypes::PortTypeEnum portType) const override
    {
        unsigned int result = 1;

        switch (portType) {
        case QExtBPTypes::PortType_In:
            result = 2;
            break;

        case QExtBPTypes::PortType_Out:
            result = 2;
            break;
        case QExtBPTypes::PortType_None:
            break;
        }

        return result;
    }

    QExtBPNodeDataType dataType(const QExtBPTypes::PortTypeEnum portType, const QExtBPTypes::PortIndex portIndex) const override
    {
        switch (portType) {
        case QExtBPTypes::PortType_In:
            switch (portIndex) {
            case 0:
                return MyNodeData().type();
            case 1:
                return SimpleNodeData().type();
            }
            break;

        case QExtBPTypes::PortType_Out:
            switch (portIndex) {
            case 0:
                return MyNodeData().type();
            case 1:
                return SimpleNodeData().type();
            }
            break;

        case QExtBPTypes::PortType_None:
            break;
        }
        // FIXME: control may reach end of non-void function [-Wreturn-type]
        return QExtBPNodeDataType();
    }

    QExtSharedPointer<QExtBPNodeData> outData(const QExtBPTypes::PortIndex port) override
    {
        if (port < 1)
            return QExtSharedPointer<MyNodeData>(new MyNodeData);

        return QExtSharedPointer<SimpleNodeData>(new SimpleNodeData);
    }

    void setInData(QExtSharedPointer<QExtBPNodeData>, const QExtBPTypes::PortIndex) override
    {
        //
    }

    QWidget *embeddedWidget() override { return QEXT_NULLPTR; }
};
