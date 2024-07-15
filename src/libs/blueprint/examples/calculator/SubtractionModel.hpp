#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLabel>

#include <QExtBlueprint>

#include "MathOperationDataModel.hpp"

#include "DecimalData.hpp"

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class SubtractionModel : public MathOperationDataModel
{
public:
    virtual ~SubtractionModel() {}

public:
    QString caption() const override { return QStringLiteral("Subtraction"); }

    virtual bool portCaptionVisible(QExtBPTypes::PortTypeEnum portType, QExtBPTypes::PortIndex portIndex) const override
    {
        Q_UNUSED(portType);
        Q_UNUSED(portIndex);
        return true;
    }

    virtual QString portCaption(QExtBPTypes::PortTypeEnum portType, QExtBPTypes::PortIndex portIndex) const override
    {
        switch (portType) {
        case QExtBPTypes::PortType_In:
            if (portIndex == 0)
                return QStringLiteral("Minuend");
            else if (portIndex == 1)
                return QStringLiteral("Subtrahend");

            break;

        case QExtBPTypes::PortType_Out:
            return QStringLiteral("Result");

        default:
            break;
        }
        return QString();
    }

    QString name() const override { return QStringLiteral("Subtraction"); }

private:
    void compute() override
    {
        QExtBPTypes::PortIndex const outPortIndex = 0;

        auto n1 = _number1.lock();
        auto n2 = _number2.lock();

        if (n1 && n2) {
            _result = qextMakeShared<DecimalData>(n1->number() - n2->number());
        } else {
            _result.reset();
        }

        Q_EMIT dataUpdated(outPortIndex);
    }
};
