#ifndef _QEXTPLOTMANAGER_H
#define _QEXTPLOTMANAGER_H

#include <qextPlotGlobal.h>
#include <qextSerializable.h>

#include <QObject>

class QExtPlotManager : public QObject, public QExtSerializable
{
    Q_OBJECT
public:
    static QExtPlotManager *instance();
    ~QExtPlotManager() QEXT_OVERRIDE;

protected:
    explicit QExtPlotManager(QObject *parent = QEXT_NULLPTR);

private:
    QEXT_DISABLE_COPY_MOVE(QExtPlotManager)
};

#endif // _QEXTPLOTMANAGER_H
