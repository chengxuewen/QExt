#pragma once

#include <QExtBlueprint>

#include <QtCore/QObject>
#include <QtWidgets/QLabel>

#include "MathOperationDataModel.hpp"
#include "DecimalData.hpp"

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class MultiplicationModel : public MathOperationDataModel
{
public:
    virtual ~MultiplicationModel() {}

public:
    QString caption() const override { return QStringLiteral("Multiplication"); }

    QString name() const override { return QStringLiteral("Multiplication"); }

private:
    void compute() override
    {
        QExtBPTypes::PortIndex const outPortIndex = 0;

        auto n1 = qextMakeSharedRef(_number1);
        auto n2 = qextMakeSharedRef(_number2);

        if (n1 && n2) {
            //modelValidationState = NodeValidationState::Valid;
            //modelValidationError = QString();
            _result = qextMakeShared<DecimalData>(n1->number() * n2->number());
        } else {
            //modelValidationState = NodeValidationState::Warning;
            //modelValidationError = QStringLiteral("Missing or incorrect inputs");
            _result.reset();
        }

        Q_EMIT dataUpdated(outPortIndex);
    }
};
