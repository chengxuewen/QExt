#pragma once

#include <QtCore/QObject>

#include "TextData.hpp"

#include <QExtBlueprint>

#include <iostream>


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

    QExtSharedPointer<QExtBPNodeData> outData(const QExtBPTypes::PortIndex portIndex) override;

    void setInData(QExtSharedPointer<QExtBPNodeData>, const QExtBPTypes::PortIndex) override {}

    QWidget *embeddedWidget() override;

private Q_SLOTS:

    void onTextEdited(const QString &string);

private:
    QLineEdit *_lineEdit;
};
