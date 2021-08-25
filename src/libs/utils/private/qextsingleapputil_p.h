#ifndef QEXTSINGLEAPPUTIL_P_H
#define QEXTSINGLEAPPUTIL_P_H

#include <qextobject_p.h>
#include <qextutilsglobal.h>
#include <qextsingleapputil.h>

#include <QObject>
#include <QLocalServer>



class QEXT_UTILS_API QEXTSingleAppUtilSlotWrapper : public QObject
{
    Q_OBJECT
public:
    QEXTSingleAppUtilSlotWrapper(QEXTSingleAppUtil *singleAppUtil, QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTSingleAppUtilSlotWrapper();

public Q_SLOTS:
    void newLocalConnectionReceived();

protected:
    QEXTSingleAppUtil *m_singleAppUtil;
};

class QEXT_UTILS_API QEXTSingleAppUtilPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTSingleAppUtilPrivate(QEXTSingleAppUtil *qq);
    ~QEXTSingleAppUtilPrivate();

    bool initLocalServer();

    QScopedPointer<QEXTSingleAppUtilSlotWrapper> m_singleAppUtilSlotWrapper;
    QScopedPointer<QLocalServer> m_localServer;
    QString m_localServerName;

private:
    QEXT_DECL_PUBLIC(QEXTSingleAppUtil)
    QEXT_DISABLE_COPY_MOVE(QEXTSingleAppUtilPrivate)
};



#endif // QEXTSINGLEAPPUTIL_P_H
