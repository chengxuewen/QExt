#pragma once

#include <QtCore/QObject>

#include "TextData.hpp"

// #include <QtNodes/NodeDelegateModel>
#include <qextBlueprintNode.h>

#include <iostream>

//using QtNodes::QExtBPNodeData;
//using QExtBPNodeDelegateModel;
//using QExtBPTypes::PortIndex;
//using QExtBPTypes::PortTypeEnum;

class QLineEdit;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class TextSourceDataModel : public QExtBPNodeDelegateModel
{
    Q_OBJECT

public:
    TextSourceDataModel();

public:
    QString caption() const override { return QString("Text Source"); }

    bool captionVisible() const override { return false; }

    static QString Name() { return QString("TextSourceDataModel"); }

    QString name() const override { return TextSourceDataModel::Name(); }

public:
    unsigned int nPorts(QExtBPTypes::PortTypeEnum portType) const override;

    QExtBPNodeDataType dataType(QExtBPTypes::PortTypeEnum portType, QExtBPTypes::PortIndex portIndex) const override;

    std::shared_ptr<QExtBPNodeData> outData(QExtBPTypes::PortIndex const portIndex) override;

    void setInData(std::shared_ptr<QExtBPNodeData>, QExtBPTypes::PortIndex const) override {}

    QWidget *embeddedWidget() override;

private Q_SLOTS:

    void onTextEdited(QString const &string);

private:
    QLineEdit *_lineEdit;
};
