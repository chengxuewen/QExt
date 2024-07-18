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

QSharedPointer<QExtBPNodeData> TextDisplayDataModel::outData(QExtBPTypes::PortIndex)
{
    QSharedPointer<QExtBPNodeData> ptr;
    return ptr;
}

void TextDisplayDataModel::setInData(QSharedPointer<QExtBPNodeData> data, const QExtBPTypes::PortIndex)
{
    auto textData = data.dynamicCast<TextData>();

    if (textData) {
        _inputText = textData->text();
    } else {
        _inputText = "";
    }

    _label->setText(_inputText);
    _label->adjustSize();
}
