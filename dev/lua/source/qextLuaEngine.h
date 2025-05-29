#ifndef _QEXTLUAENGINE_H
#define _QEXTLUAENGINE_H

#include <qextLuaGlobal.h>

#include <QObject>

class QExtLuaEnginePrivate;
class QEXT_LUA_API QExtLuaEngine : public QObject
{
    Q_OBJECT

public:
    explicit QExtLuaEngine(QObject *parent = QEXT_NULLPTR);
    ~QExtLuaEngine() QEXT_OVERRIDE;


protected:
    QScopedPointer<QExtLuaEnginePrivate> dd_ptr;

private:
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtLuaEngine)
    QEXT_DISABLE_COPY_MOVE(QExtLuaEngine)
};

#endif // _QEXTLUAENGINE_H
