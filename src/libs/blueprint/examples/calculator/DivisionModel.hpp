#pragma once

#include "DecimalData.hpp"
#include "MathOperationDataModel.hpp"

#include <QExtBlueprint>

#include <QtCore/QObject>
#include <QtWidgets/QLabel>

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class DivisionModel : public MathOperationDataModel
{
public:
    virtual ~DivisionModel() {}

public:
    QString caption() const override { return QStringLiteral("Division"); }

    bool portCaptionVisible(QExtBPTypes::PortTypeEnum portType, QExtBPTypes::PortIndex portIndex) const override
    {
        Q_UNUSED(portType);
        Q_UNUSED(portIndex);
        return true;
    }

    QString portCaption(QExtBPTypes::PortTypeEnum portType, QExtBPTypes::PortIndex portIndex) const override
    {
        switch (portType) {
        case QExtBPTypes::PortType_In:
            if (portIndex == 0)
                return QStringLiteral("Dividend");
            else if (portIndex == 1)
                return QStringLiteral("Divisor");

            break;

        case QExtBPTypes::PortType_Out:
            return QStringLiteral("Result");

        default:
            break;
        }
        return QString();
    }

    QString name() const override { return QStringLiteral("Division"); }

private:
    void compute() override
    {
        const QExtBPTypes::PortIndex outPortIndex = 0;

        auto n1 = qextMakeSharedRef(_number1);
        auto n2 = qextMakeSharedRef(_number2);

        if (n2 && (n2->number() == 0.0)) {
            //modelValidationState = NodeValidationState::Error;
            //modelValidationError = QStringLiteral("Division by zero error");
            _result.reset();
        } else if (n1 && n2) {
            //modelValidationState = NodeValidationState::Valid;
            //modelValidationError = QString();
            _result = qextMakeShared<DecimalData>(n1->number() / n2->number());
        } else {
            //modelValidationState = NodeValidationState::Warning;
            //modelValidationError = QStringLiteral("Missing or incorrect inputs");
            _result.reset();
        }

        Q_EMIT dataUpdated(outPortIndex);
    }
};
