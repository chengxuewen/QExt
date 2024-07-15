#pragma once

#include <iostream>

#include <QtCore/QObject>
#include <QtWidgets/QLabel>

#include <QExtBlueprint>

#include "PixmapData.hpp"

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class ImageLoaderModel : public QExtBPNodeDelegateModel
{
    Q_OBJECT

public:
    ImageLoaderModel();

    ~ImageLoaderModel() = default;

public:
    QString caption() const override { return QString("Image Source"); }

    QString name() const override { return QString("ImageLoaderModel"); }

public:
    virtual QString modelName() const { return QString("Source Image"); }

    unsigned int nPorts(QExtBPTypes::PortTypeEnum const portType) const override;

    QExtBPNodeDataType dataType(QExtBPTypes::PortTypeEnum const portType, QExtBPTypes::PortIndex const portIndex) const override;

    QSharedPointer<QExtBPNodeData> outData(QExtBPTypes::PortIndex const port) override;

    void setInData(QSharedPointer<QExtBPNodeData>, QExtBPTypes::PortIndex const portIndex) override {}

    QWidget *embeddedWidget() override { return _label; }

    bool resizable() const override { return true; }

protected:
    bool eventFilter(QObject *object, QEvent *event) override;

private:
    QLabel *_label;

    QPixmap _pixmap;
};
