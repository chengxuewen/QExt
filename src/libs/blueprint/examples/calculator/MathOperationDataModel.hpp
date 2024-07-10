#pragma once

#include <QExtBlueprint>

#include <QtCore/QJsonObject>
#include <QtCore/QObject>
#include <QtWidgets/QLabel>

#include <iostream>

class DecimalData;

//using QtNodes::QExtBPNodeData;
//using QtNodes::QExtBPNodeDataType;
//using QExtBPNodeDelegateModel;
//using QExtBPTypes::PortIndex;
//using QExtBPTypes::PortTypeEnum;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class MathOperationDataModel : public QExtBPNodeDelegateModel
{
    Q_OBJECT

public:
    ~MathOperationDataModel() = default;

public:
    unsigned int nPorts(QExtBPTypes::PortTypeEnum portType) const override;

    QExtBPNodeDataType dataType(QExtBPTypes::PortTypeEnum portType, QExtBPTypes::PortIndex portIndex) const override;

    std::shared_ptr<QExtBPNodeData> outData(QExtBPTypes::PortIndex port) override;

    void setInData(std::shared_ptr<QExtBPNodeData> data, QExtBPTypes::PortIndex portIndex) override;

    QWidget *embeddedWidget() override { return nullptr; }

protected:
    virtual void compute() = 0;

protected:
    std::weak_ptr<DecimalData> _number1;
    std::weak_ptr<DecimalData> _number2;

    std::shared_ptr<DecimalData> _result;
};
