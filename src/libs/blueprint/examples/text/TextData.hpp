#pragma once

#include <QExtBlueprint>

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class TextData : public QExtBPNodeData
{
public:
    TextData() {}

    TextData(const QString &text)
        : _text(text)
    {}

    QExtBPNodeDataType type() const override { return QExtBPNodeDataType{"text", "Text"}; }

    QString text() const { return _text; }

private:
    QString _text;
};
