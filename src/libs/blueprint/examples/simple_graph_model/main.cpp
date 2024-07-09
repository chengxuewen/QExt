// #include <QtNodes/BasicGraphicsScene>
// #include <QtNodes/ConnectionStyle>
// #include <QtNodes/GraphicsView>
// #include <QtNodes/StyleCollection>
#include <qextBlueprintNode.h>

#include <QAction>
#include <QScreen>
#include <QtWidgets/QApplication>

#include "SimpleGraphModel.hpp"

//using QExtBPBasicGraphicsScene;
//using QtNodes::QExtBPConnectionStyle;
//using QtNodes::QExtBPGraphicsView;
//using QtNodes::NodeRole;
//using QtNodes::QExtBPStyleCollection;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    SimpleGraphModel graphModel;

    // Initialize and connect two nodes.
    {
        QExtBPTypes::NodeId id1 = graphModel.addNode();
        graphModel.setNodeData(id1, QExtBPTypes::NodeRole_Position, QPointF(0, 0));

        QExtBPTypes::NodeId id2 = graphModel.addNode();
        graphModel.setNodeData(id2, QExtBPTypes::NodeRole_Position, QPointF(300, 300));

        graphModel.addConnection(QExtBPTypes::ConnectionId{id1, 0, id2, 0});
    }

    auto scene = new QExtBPBasicGraphicsScene(graphModel);

    QExtBPGraphicsView view(scene);

    // Setup context menu for creating new nodes.
    view.setContextMenuPolicy(Qt::ActionsContextMenu);
    QAction createNodeAction(QStringLiteral("Create Node"), &view);
    QObject::connect(&createNodeAction, &QAction::triggered, [&]() {
        // Mouse position in scene coordinates.
        QPointF posView = view.mapToScene(view.mapFromGlobal(QCursor::pos()));

        QExtBPTypes::NodeId const newId = graphModel.addNode();
        graphModel.setNodeData(newId, QExtBPTypes::NodeRole_Position, posView);
    });
    view.insertAction(view.actions().front(), &createNodeAction);

    view.setWindowTitle("Simple Node Graph");
    view.resize(800, 600);

    // Center window.
    view.move(QApplication::primaryScreen()->availableGeometry().center() - view.rect().center());
    view.showNormal();

    return app.exec();
}
