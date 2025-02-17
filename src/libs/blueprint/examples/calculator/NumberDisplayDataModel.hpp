#pragma once

#include <QExtBlueprint>

#include <QtCore/QObject>

#include <iostream>

#include "DecimalData.hpp"

class QLabel;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class NumberDisplayDataModel : public QExtBPNodeDelegateModel
{
    Q_OBJECT

public:
    NumberDisplayDataModel();

    ~NumberDisplayDataModel() = default;

public:
    QString caption() const override { return QStringLiteral("Result"); }

    bool captionVisible() const override { return false; }

    QString name() const override { return QStringLiteral("Result"); }

public:
    unsigned int nPorts(QExtBPTypes::PortTypeEnum portType) const override;

    QExtBPNodeDataType dataType(QExtBPTypes::PortTypeEnum portType, QExtBPTypes::PortIndex portIndex) const override;

    QExtSharedPointer<QExtBPNodeData> outData(QExtBPTypes::PortIndex port) override;

    void setInData(QExtSharedPointer<QExtBPNodeData> data, QExtBPTypes::PortIndex portIndex) override;

    QWidget *embeddedWidget() override;

    double number() const;

private:
    QExtSharedPointer<DecimalData> _numberData;

    QLabel *_label;
};
