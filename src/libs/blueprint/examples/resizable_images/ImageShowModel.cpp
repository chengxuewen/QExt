#include "ImageShowModel.hpp"

#include "PixmapData.hpp"

#include <QExtBlueprint>

#include <QtCore/QDir>
#include <QtCore/QEvent>
#include <QtWidgets/QFileDialog>

ImageShowModel::ImageShowModel()
    : _label(new QLabel("Image will appear here"))
{
    _label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    QFont f = _label->font();
    f.setBold(true);
    f.setItalic(true);

    _label->setFont(f);

    _label->setMinimumSize(200, 200);

    _label->installEventFilter(this);
}

unsigned int ImageShowModel::nPorts(QExtBPTypes::PortTypeEnum portType) const
{
    unsigned int result = 1;

    switch (portType) {
    case QExtBPTypes::PortType_In:
        result = 1;
        break;

    case QExtBPTypes::PortType_Out:
        result = 1;

    default:
        break;
    }

    return result;
}

bool ImageShowModel::eventFilter(QObject *object, QEvent *event)
{
    if (object == _label) {
        int w = _label->width();
        int h = _label->height();

        if (event->type() == QEvent::Resize) {
            auto d = qextDynamicPointerCast<PixmapData>(_nodeData);
            if (d) {
                _label->setPixmap(d->pixmap().scaled(w, h, Qt::KeepAspectRatio));
            }
        }
    }

    return false;
}

QExtBPNodeDataType ImageShowModel::dataType(const QExtBPTypes::PortTypeEnum, const QExtBPTypes::PortIndex) const
{
    return PixmapData().type();
}

QExtSharedPointer<QExtBPNodeData> ImageShowModel::outData(QExtBPTypes::PortIndex)
{
    return _nodeData;
}

void ImageShowModel::setInData(QExtSharedPointer<QExtBPNodeData> nodeData, const QExtBPTypes::PortIndex)
{
    _nodeData = nodeData;

    if (_nodeData)
    {
        auto d = qextDynamicPointerCast<PixmapData>(_nodeData);

        int w = _label->width();
        int h = _label->height();

        _label->setPixmap(d->pixmap().scaled(w, h, Qt::KeepAspectRatio));
    }
    else
    {
        _label->setPixmap(QPixmap());
    }

    Q_EMIT dataUpdated(0);
}
