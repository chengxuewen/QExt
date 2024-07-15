#pragma once

#include <QExtBlueprint>

#include <QtCore/QObject>

#include <iostream>

class DecimalData;

//using QtNodes::QExtBPNodeData;
//using QtNodes::QExtBPNodeDataType;
//using QExtBPNodeDelegateModel;
//using QExtBPTypes::PortIndex;
//using QExtBPTypes::PortTypeEnum;

class QLineEdit;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class NumberSourceDataModel : public QExtBPNodeDelegateModel
{
    Q_OBJECT

public:
    NumberSourceDataModel();

    virtual ~NumberSourceDataModel() {}

public:
    QString caption() const override { return QStringLiteral("Number Source"); }

    bool captionVisible() const override { return false; }

    QString name() const override { return QStringLiteral("NumberSource"); }

public:
    QJsonObject save() const override;

    void load(QJsonObject const &p) override;

public:
    unsigned int nPorts(QExtBPTypes::PortTypeEnum portType) const override;

    QExtBPNodeDataType dataType(QExtBPTypes::PortTypeEnum portType, QExtBPTypes::PortIndex portIndex) const override;

    QSharedPointer<QExtBPNodeData> outData(QExtBPTypes::PortIndex port) override;

    void setInData(QSharedPointer<QExtBPNodeData>, QExtBPTypes::PortIndex) override {}

    QWidget *embeddedWidget() override;

public:
    void setNumber(double number);

private Q_SLOTS:

    void onTextEdited(QString const &string);

private:
    QSharedPointer<DecimalData> _number;

    QLineEdit *_lineEdit;
};
