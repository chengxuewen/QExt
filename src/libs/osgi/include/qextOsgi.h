#ifndef _QEXTOSGI_H
#define _QEXTOSGI_H

#include <qextOsgiGlobal.h>

#include <QObject>

class QEXT_OSGI_API QEXTOsgi : public QObject
{
    Q_OBJECT
public:
    explicit QEXTOsgi(QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTOsgi();
};

#endif // _QEXTOSGI_H
