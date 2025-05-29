#include <private/qextLuaEngine_p.h>

#include <QDebug>

QExtLuaEnginePrivate::QExtLuaEnginePrivate(QExtLuaEngine *q)
    : q_ptr(q)
{
}

QExtLuaEnginePrivate::~QExtLuaEnginePrivate()
{
}

QExtLuaEngine::QExtLuaEngine(QObject *parent)
    : QObject(parent)
{
}

QExtLuaEngine::~QExtLuaEngine()
{

}
