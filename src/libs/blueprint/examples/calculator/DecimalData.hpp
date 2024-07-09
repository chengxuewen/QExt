#pragma once

// #include <QtNodes/NodeData>
#include <qextBlueprintNode.h>

//using QtNodes::QExtBPNodeData;
//using QtNodes::QExtBPNodeDataType;

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class DecimalData : public QExtBPNodeData
{
public:
    DecimalData()
        : _number(0.0)
    {}

    DecimalData(double const number)
        : _number(number)
    {}

    QExtBPNodeDataType type() const override { return QExtBPNodeDataType{"decimal", "Decimal"}; }

    double number() const { return _number; }

    QString numberAsText() const { return QString::number(_number, 'f'); }

private:
    double _number;
};
