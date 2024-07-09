#include "NumberDisplayDataModel.hpp"

#include <QtWidgets/QLabel>

NumberDisplayDataModel::NumberDisplayDataModel()
    : _label{nullptr}
{}

unsigned int NumberDisplayDataModel::nPorts(QExtBPTypes::PortTypeEnum portType) const
{
    unsigned int result = 1;

    switch (portType) {
    case QExtBPTypes::PortType_In:
        result = 1;
        break;

    case QExtBPTypes::PortType_Out:
        result = 0;

    default:
        break;
    }

    return result;
}

QExtBPNodeDataType NumberDisplayDataModel::dataType(QExtBPTypes::PortTypeEnum, QExtBPTypes::PortIndex) const
{
    return DecimalData().type();
}

std::shared_ptr<QExtBPNodeData> NumberDisplayDataModel::outData(QExtBPTypes::PortIndex)
{
    std::shared_ptr<QExtBPNodeData> ptr;
    return ptr;
}

void NumberDisplayDataModel::setInData(std::shared_ptr<QExtBPNodeData> data, QExtBPTypes::PortIndex portIndex)
{
    _numberData = std::dynamic_pointer_cast<DecimalData>(data);

    if (!_label)
        return;

    if (_numberData) {
        _label->setText(_numberData->numberAsText());
    } else {
        _label->clear();
    }

    _label->adjustSize();
}

QWidget *NumberDisplayDataModel::embeddedWidget()
{
    if (!_label) {
        _label = new QLabel();
        _label->setMargin(3);
    }

    return _label;
}

double NumberDisplayDataModel::number() const
{
    if (_numberData)
        return _numberData->number();

    return 0.0;
}
