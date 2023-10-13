#ifndef COLOREDPIXMAPICONENGINE_H
#define COLOREDPIXMAPICONENGINE_H

#include <qextColoredPixmapIconGlobal.h>

#include <QtGui/private/qicon_p.h>

class QEXT_COLOREDPIXMAPICON_API QExtColoredPixmapIconEngine : public QPixmapIconEngine
{
public:
    QPixmap pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state) QEXT_DECL_OVERRIDE;
};

#endif // COLOREDPIXMAPICONENGINE_H
