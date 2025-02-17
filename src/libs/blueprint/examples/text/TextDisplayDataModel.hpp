#pragma once

#include "TextData.hpp"

#include <QExtBlueprint>

#include <QtCore/QObject>
#include <QtWidgets/QLabel>

#include <iostream>
#include <vector>


/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class TextDisplayDataModel : public QExtBPNodeDelegateModel
{
    Q_OBJECT

public:
    TextDisplayDataModel();

    virtual ~TextDisplayDataModel() {}

public:
    QString caption() const override { return QString("Text Display"); }

    bool captionVisible() const override { return false; }

    static QString Name() { return QString("TextDisplayDataModel"); }

    QString name() const override { return TextDisplayDataModel::Name(); }

public:
    unsigned int nPorts(QExtBPTypes::PortTypeEnum portType) const override;

    QExtBPNodeDataType dataType(QExtBPTypes::PortTypeEnum portType, QExtBPTypes::PortIndex portIndex) const override;

    QExtSharedPointer<QExtBPNodeData> outData(const QExtBPTypes::PortIndex port) override;

    void setInData(QExtSharedPointer<QExtBPNodeData> data, const QExtBPTypes::PortIndex portIndex) override;

    QWidget *embeddedWidget() override { return _label; }

private:
    QLabel *_label;
    QString _inputText;
};
