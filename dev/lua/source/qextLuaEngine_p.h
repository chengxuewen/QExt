#ifndef _QEXTLUAENGINE_P_H
#define _QEXTLUAENGINE_P_H

#include <qextLuaEngine.h>

class QEXT_LUA_API QExtLuaEnginePrivate
{
public:
    explicit QExtLuaEnginePrivate(QExtLuaEngine *q);
    virtual ~QExtLuaEnginePrivate();

    QExtLuaEngine * const q_ptr;

private:
    QEXT_DECL_PUBLIC(QExtLuaEngine)
    QEXT_DISABLE_COPY_MOVE(QExtLuaEnginePrivate)
};

#endif // _QEXTLUAENGINE_P_H
