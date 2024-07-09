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

std::shared_ptr<QExtBPNodeData> MathOperationDataModel::outData(QExtBPTypes::PortIndex)
{
    return std::static_pointer_cast<QExtBPNodeData>(_result);
}

void MathOperationDataModel::setInData(std::shared_ptr<QExtBPNodeData> data, QExtBPTypes::PortIndex portIndex)
{
    auto numberData = std::dynamic_pointer_cast<DecimalData>(data);

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
