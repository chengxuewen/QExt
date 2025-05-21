#include "NumberSourceDataModel.hpp"

#include "DecimalData.hpp"

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>
#include <QtWidgets/QLineEdit>

NumberSourceDataModel::NumberSourceDataModel()
    : _lineEdit(QEXT_NULLPTR)
    , _number(qextMakeShared<DecimalData>(0.0))
{}

QJsonObject NumberSourceDataModel::save() const
{
    QJsonObject modelJson = QExtBPNodeDelegateModel::save();

    modelJson["number"] = QString::number(_number->number());

    return modelJson;
}

void NumberSourceDataModel::load(const QJsonObject &p)
{
    QJsonValue v = p["number"];

    if (!v.isUndefined()) {
        QString strNum = v.toString();

        bool ok;
        double d = strNum.toDouble(&ok);
        if (ok) {
            _number = qextMakeShared<DecimalData>(d);

            if (_lineEdit)
                _lineEdit->setText(strNum);
        }
    }
}

unsigned int NumberSourceDataModel::nPorts(QExtBPTypes::PortTypeEnum portType) const
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

void NumberSourceDataModel::onTextEdited(const QString &str)
{
    bool ok = false;

    double number = str.toDouble(&ok);

    if (ok) {
        _number = qextMakeShared<DecimalData>(number);

        Q_EMIT dataUpdated(0);

    } else {
        Q_EMIT dataInvalidated(0);
    }
}

QExtBPNodeDataType NumberSourceDataModel::dataType(QExtBPTypes::PortTypeEnum, QExtBPTypes::PortIndex) const
{
    return DecimalData().type();
}

QExtSharedPointer<QExtBPNodeData> NumberSourceDataModel::outData(QExtBPTypes::PortIndex)
{
    return _number;
}

QWidget *NumberSourceDataModel::embeddedWidget()
{
    if (!_lineEdit) {
        _lineEdit = new QLineEdit();

        _lineEdit->setValidator(new QDoubleValidator());
        _lineEdit->setMaximumSize(_lineEdit->sizeHint());

        connect(_lineEdit, &QLineEdit::textChanged, this, &NumberSourceDataModel::onTextEdited);

        _lineEdit->setText(QString::number(_number->number()));
    }

    return _lineEdit;
}

void NumberSourceDataModel::setNumber(double n)
{
    _number = qextMakeShared<DecimalData>(n);

    Q_EMIT dataUpdated(0);

    if (_lineEdit)
        _lineEdit->setText(QString::number(_number->number()));
}
