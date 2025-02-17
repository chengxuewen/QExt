#pragma once

#include "DecimalData.hpp"
#include "MathOperationDataModel.hpp"

#include <QExtBlueprint>

#include <QtCore/QObject>
#include <QtWidgets/QLabel>

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class AdditionModel : public MathOperationDataModel
{
public:
    ~AdditionModel() = default;

public:
    QString caption() const override { return QStringLiteral("Addition"); }

    QString name() const override { return QStringLiteral("Addition"); }

private:
    void compute() override
    {
        const QExtBPTypes::PortIndex outPortIndex = 0;

        auto n1 = qextMakeSharedRef(_number1);
        auto n2 = qextMakeSharedRef(_number2);

        if (n1 && n2) {
            _result = qextMakeShared<DecimalData>(n1->number() + n2->number());
        } else {
            _result.reset();
        }

        Q_EMIT dataUpdated(outPortIndex);
    }
};
