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

QExtSharedPointer<QExtBPNodeData> MathOperationDataModel::outData(QExtBPTypes::PortIndex)
{
    return _result;
}

void MathOperationDataModel::setInData(QExtSharedPointer<QExtBPNodeData> data, QExtBPTypes::PortIndex portIndex)
{
    QExtSharedPointer<DecimalData> numberData = qextDynamicPointerCast<DecimalData>(data);

    if (!data) {
        Q_EMIT dataInvalidated(0);
    }

    if (portIndex == 0) {
        _number1 = qextMakeWeakRef(numberData);
    } else {
        _number2 = qextMakeWeakRef(numberData);
    }

    compute();
}
