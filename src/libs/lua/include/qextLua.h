#ifndef _QEXTLUA_H
#define _QEXTLUA_H

#include <qextLuaGlobal.h>

#include <QObject>

class QEXT_LUA_API QEXTLua : public QObject
{
    Q_OBJECT
public:
    explicit QEXTLua(QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTLua();
};

#endif // _QEXTLUA_H
