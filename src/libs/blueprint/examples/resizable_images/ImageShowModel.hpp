#pragma once

#include <iostream>

#include <QtCore/QObject>
#include <QtWidgets/QLabel>

#include <QExtBlueprint>


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

    unsigned int nPorts(const QExtBPTypes::PortTypeEnum portType) const override;

    QExtBPNodeDataType dataType(const QExtBPTypes::PortTypeEnum portType, const QExtBPTypes::PortIndex portIndex) const override;

    QExtSharedPointer<QExtBPNodeData> outData(const QExtBPTypes::PortIndex port) override;

    void setInData(QExtSharedPointer<QExtBPNodeData> nodeData, const QExtBPTypes::PortIndex port) override;

    QWidget *embeddedWidget() override { return _label; }

    bool resizable() const override { return true; }

protected:
    bool eventFilter(QObject *object, QEvent *event) override;

private:
    QLabel *_label;

    QExtSharedPointer<QExtBPNodeData> _nodeData;
};
