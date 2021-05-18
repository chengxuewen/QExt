#ifndef QEXTSINGLEAPPUTIL_H
#define QEXTSINGLEAPPUTIL_H

#include <qextutilsglobal.h>
#include <qextobject.h>

#include <QObject>



class QEXTSingleAppUtilPrivate;
class QEXT_UTILS_API QEXTSingleAppUtil : public QEXTObject
{
public:
    QEXTSingleAppUtil();
    QEXTSingleAppUtil(QEXTSingleAppUtilPrivate &dd);
    ~QEXTSingleAppUtil();

    bool initLocalConnection();
    virtual void newLocalConnectionReceived();

private:
    QEXT_DECLARE_PRIVATE(QEXTSingleAppUtil)
    QEXT_DISABLE_COPY_MOVE(QEXTSingleAppUtil)
};



#endif // QEXTSINGLEAPPUTIL_H
