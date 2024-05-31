#ifndef _QEXTWEBCLASSHANDLER_H
#define _QEXTWEBCLASSHANDLER_H

#include <qextWebGlobal.h>

#include <QObject>

class QEXT_WEB_API QExtWebClassHandler : public QObject
{
    Q_OBJECT
public:
    explicit QExtWebClassHandler(QObject *parent = nullptr);

signals:

};

#endif // _QEXTWEBCLASSHANDLER_H
