#ifndef _QEXTBPDATAFLOWGRAPHICSSCENE_H
#define _QEXTBPDATAFLOWGRAPHICSSCENE_H

#include <qextBPBasicGraphicsScene.h>
#include <qextBPDataFlowGraphModel.h>
#include <qextBlueprintGlobal.h>

/**
 * @brief An advanced scene working with data-propagating graphs.
 * The class represents a scene that existed in v2.x but built wit the new model-view approach in mind.
 */
class QExtBPDataFlowGraphicsScenePrivate;
class QEXT_BLUEPRINT_API QExtBPDataFlowGraphicsScene : public QExtBPBasicGraphicsScene
{
    Q_OBJECT
public:
    QExtBPDataFlowGraphicsScene(QExtBPDataFlowGraphModel &graphModel, QObject *parent = QEXT_NULLPTR);

    ~QExtBPDataFlowGraphicsScene() = default;

    std::vector<QExtBPTypes::NodeId> selectedNodes() const;

    QMenu *createSceneMenu(const QPointF scenePos) override;

Q_SIGNALS:
    void sceneLoaded();

public Q_SLOTS:
    void save() const;

    void load();

protected Q_SLOTS:
    void onInPortDataWasSeted(const QExtBPTypes::NodeId nodeId,
                              const QExtBPTypes::PortTypeEnum,
                              const QExtBPTypes::PortIndex);

private:
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtBPDataFlowGraphicsScene)
    QEXT_DISABLE_COPY_MOVE(QExtBPDataFlowGraphicsScene)

};

#endif // _QEXTBPDATAFLOWGRAPHICSSCENE_H
