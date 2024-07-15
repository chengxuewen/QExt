#ifndef _QEXTBPDATAFLOWGRAPHICSSCENE_H
#define _QEXTBPDATAFLOWGRAPHICSSCENE_H

#include <qextBPBasicGraphicsScene.h>
#include <qextBPDataFlowGraphModel.h>
#include <qextBlueprintGlobal.h>

/// @brief An advanced scene working with data-propagating graphs.
/**
 * The class represents a scene that existed in v2.x but built wit the
 * new model-view approach in mind.
 */
class QEXT_BLUEPRINT_API QExtBPDataFlowGraphicsScene : public QExtBPBasicGraphicsScene
{
    Q_OBJECT
public:
    QExtBPDataFlowGraphicsScene(QExtBPDataFlowGraphModel &graphModel, QObject *parent = QEXT_NULLPTR);

    ~QExtBPDataFlowGraphicsScene() = default;

public:
    std::vector<QExtBPTypes::NodeId> selectedNodes() const;

public:
    QMenu *createSceneMenu(QPointF const scenePos) override;

public Q_SLOTS:
    void save() const;

    void load();

Q_SIGNALS:
    void sceneLoaded();

private:
    QExtBPDataFlowGraphModel &_graphModel;
};

#endif // _QEXTBPDATAFLOWGRAPHICSSCENE_H
