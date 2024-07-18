#include "TextSourceDataModel.hpp"

#include <QtWidgets/QLineEdit>

TextSourceDataModel::TextSourceDataModel()
    : _lineEdit(QEXT_NULLPTR)
{
    //
}

unsigned int TextSourceDataModel::nPorts(QExtBPTypes::PortTypeEnum portType) const
{
    unsigned int result = 1;

    switch (portType) {
    case QExtBPTypes::PortType_In:
        result = 0;
        break;

    case QExtBPTypes::PortType_Out:
        result = 1;

    default:
        break;
    }

    return result;
}

void TextSourceDataModel::onTextEdited(const QString &string)
{
    Q_UNUSED(string);

    Q_EMIT dataUpdated(0);
}

QExtBPNodeDataType TextSourceDataModel::dataType(QExtBPTypes::PortTypeEnum, QExtBPTypes::PortIndex) const
{
    return TextData().type();
}

QSharedPointer<QExtBPNodeData> TextSourceDataModel::outData(const QExtBPTypes::PortIndex portIndex)
{
    Q_UNUSED(portIndex);
    return qextMakeShared<TextData>(_lineEdit->text());
}

QWidget *TextSourceDataModel::embeddedWidget()
{
    if (!_lineEdit) {
        _lineEdit = new QLineEdit("Default Text"),

        connect(_lineEdit, &QLineEdit::textEdited, this, &TextSourceDataModel::onTextEdited);
    }

    return _lineEdit;
}
