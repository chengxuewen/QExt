#pragma once

#include <QtGui/QPixmap>

#include <QExtBlueprint>


/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class PixmapData : public QExtBPNodeData
{
public:
    PixmapData() {}

    PixmapData(const QPixmap &pixmap)
        : _pixmap(pixmap)
    {}

    QExtBPNodeDataType type() const override
    {
        //       id      name
        return {"pixmap", "P"};
    }

    QPixmap pixmap() const { return _pixmap; }

private:
    QPixmap _pixmap;
};
