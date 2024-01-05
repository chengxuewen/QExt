#ifndef _QEXTGRAPHICS_H
#define _QEXTGRAPHICS_H

#include <qextGraphicsGlobal.h>

#include <QObject>

class QEXT_GRAPHICS_API QExtGraphics : public QObject
{
    Q_OBJECT

public:
    explicit QExtGraphics(QObject *parent = QEXT_NULLPTR);

signals:
};

#endif // _QEXTGRAPHICS_H
