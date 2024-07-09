#pragma once

#include <iostream>

#include <QtCore/QObject>
#include <QtWidgets/QLabel>

// #include <QtNodes/NodeDelegateModel>
// #include <QtNodes/NodeDelegateModelRegistry>
#include <qextBlueprintNode.h>

//using QtNodes::QExtBPNodeData;
//using QtNodes::QExtBPNodeDataType;
//using QExtBPNodeDelegateModel;
//using QExtBPTypes::PortIndex;
//using QExtBPTypes::PortTypeEnum;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class ImageShowModel : public QExtBPNodeDelegateModel
{
    Q_OBJECT

public:
    ImageShowModel();

    ~ImageShowModel() = default;

public:
    QString caption() const override { return QString("Image Display"); }

    QString name() const override { return QString("ImageShowModel"); }

public:
    virtual QString modelName() const { return QString("Resulting Image"); }

    unsigned int nPorts(QExtBPTypes::PortTypeEnum const portType) const override;

    QExtBPNodeDataType dataType(QExtBPTypes::PortTypeEnum const portType, QExtBPTypes::PortIndex const portIndex) const override;

    std::shared_ptr<QExtBPNodeData> outData(QExtBPTypes::PortIndex const port) override;

    void setInData(std::shared_ptr<QExtBPNodeData> nodeData, QExtBPTypes::PortIndex const port) override;

    QWidget *embeddedWidget() override { return _label; }

    bool resizable() const override { return true; }

protected:
    bool eventFilter(QObject *object, QEvent *event) override;

private:
    QLabel *_label;

    std::shared_ptr<QExtBPNodeData> _nodeData;
};
