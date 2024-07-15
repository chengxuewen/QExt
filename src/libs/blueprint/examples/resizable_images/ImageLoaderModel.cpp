#include "ImageLoaderModel.hpp"

#include <QtCore/QDir>
#include <QtCore/QEvent>

#include <QtWidgets/QFileDialog>

ImageLoaderModel::ImageLoaderModel()
    : _label(new QLabel("Double click to load image"))
{
    _label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    QFont f = _label->font();
    f.setBold(true);
    f.setItalic(true);

    _label->setFont(f);

    _label->setMinimumSize(200, 200);
    _label->setMaximumSize(500, 300);

    _label->installEventFilter(this);
}

unsigned int ImageLoaderModel::nPorts(QExtBPTypes::PortTypeEnum portType) const
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

bool ImageLoaderModel::eventFilter(QObject *object, QEvent *event)
{
    if (object == _label) {
        int w = _label->width();
        int h = _label->height();

        if (event->type() == QEvent::MouseButtonPress) {
            QString fileName = QFileDialog::getOpenFileName(QEXT_NULLPTR,
                                                            tr("Open Image"),
                                                            QDir::homePath(),
                                                            tr("Image Files (*.png *.jpg *.bmp)"));

            _pixmap = QPixmap(fileName);

            _label->setPixmap(_pixmap.scaled(w, h, Qt::KeepAspectRatio));

            Q_EMIT dataUpdated(0);

            return true;
        } else if (event->type() == QEvent::Resize) {
            if (!_pixmap.isNull())
                _label->setPixmap(_pixmap.scaled(w, h, Qt::KeepAspectRatio));
        }
    }

    return false;
}

QExtBPNodeDataType ImageLoaderModel::dataType(QExtBPTypes::PortTypeEnum const, QExtBPTypes::PortIndex const) const
{
    return PixmapData().type();
}

QSharedPointer<QExtBPNodeData> ImageLoaderModel::outData(QExtBPTypes::PortIndex)
{
    return qextMakeShared<PixmapData>(_pixmap);
}
