#include "MathOperationDataModel.hpp"

#include "DecimalData.hpp"

unsigned int MathOperationDataModel::nPorts(QExtBPTypes::PortTypeEnum portType) const
{
    unsigned int result;

    if (portType == QExtBPTypes::PortType_In)
        result = 2;
    else
        result = 1;

    return result;
}

QExtBPNodeDataType MathOperationDataModel::dataType(QExtBPTypes::PortTypeEnum, QExtBPTypes::PortIndex) const
{
    return DecimalData().type();
}

QSharedPointer<QExtBPNodeData> MathOperationDataModel::outData(QExtBPTypes::PortIndex)
{
    return _result;
}

void MathOperationDataModel::setInData(QSharedPointer<QExtBPNodeData> data, QExtBPTypes::PortIndex portIndex)
{
    QSharedPointer<DecimalData> numberData = data.dynamicCast<DecimalData>();

    if (!data) {
        Q_EMIT dataInvalidated(0);
    }

    if (portIndex == 0) {
        _number1 = numberData;
    } else {
        _number2 = numberData;
    }

    compute();
}
