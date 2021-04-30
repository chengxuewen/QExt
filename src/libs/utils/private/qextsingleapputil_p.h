#ifndef QEXTSINGLEAPPUTIL_P_H
#define QEXTSINGLEAPPUTIL_P_H

#include <qextobject_p.h>
#include <qextutilsglobal.h>

#include <QObject>
#include <QLocalServer>

class QEXTSingleAppUtil;
class QEXT_UTILS_API QEXTSingleAppUtilPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTSingleAppUtilPrivate(QEXTSingleAppUtil *qq);
    ~QEXTSingleAppUtilPrivate();

    bool initLocalServer();

    QScopedPointer<QLocalServer> m_localServer;
    QString m_localServerName;

private:
    QEXT_DECLARE_PUBLIC(QEXTSingleAppUtil)
    QEXT_DISABLE_COPY_MOVE(QEXTSingleAppUtilPrivate)
};

#endif // QEXTSINGLEAPPUTIL_P_H
