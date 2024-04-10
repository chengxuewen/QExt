#ifndef _QEXTBLUEPRINTSCENE_P_H
#define _QEXTBLUEPRINTSCENE_P_H

#include <qextBlueprintScene.h>

class QExtBlueprintScenePrivate
{
    QExtBlueprintScene * const q_ptr;
public:
    explicit QExtBlueprintScenePrivate(QExtBlueprintScene *q);
    virtual ~QExtBlueprintScenePrivate();

    QGraphicsView *m_view;

private:
    QEXT_DECL_PUBLIC(QExtBlueprintScene)
    QEXT_DISABLE_COPY_MOVE(QExtBlueprintScenePrivate)
};

#endif // _QEXTBLUEPRINTSCENE_P_H
