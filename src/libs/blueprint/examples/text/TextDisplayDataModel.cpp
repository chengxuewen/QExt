#include "TextDisplayDataModel.hpp"

TextDisplayDataModel::TextDisplayDataModel()
    : _label(new QLabel("Resulting Text"))
{
    _label->setMargin(3);
}

unsigned int TextDisplayDataModel::nPorts(QExtBPTypes::PortTypeEnum portType) const
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

QExtBPNodeDataType TextDisplayDataModel::dataType(QExtBPTypes::PortTypeEnum, QExtBPTypes::PortIndex) const
{
    return TextData().type();
}

std::shared_ptr<QExtBPNodeData> TextDisplayDataModel::outData(QExtBPTypes::PortIndex)
{
    std::shared_ptr<QExtBPNodeData> ptr;
    return ptr;
}

void TextDisplayDataModel::setInData(std::shared_ptr<QExtBPNodeData> data, QExtBPTypes::PortIndex const)
{
    auto textData = std::dynamic_pointer_cast<TextData>(data);

    if (textData) {
        _inputText = textData->text();
    } else {
        _inputText = "";
    }

    _label->setText(_inputText);
    _label->adjustSize();
}
