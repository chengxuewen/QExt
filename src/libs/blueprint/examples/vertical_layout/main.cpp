#include <QAction>
#include <QScreen>
#include <QApplication>
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QGroupBox>
#include <QRadioButton>

#include <QExtBlueprint>

#include "SimpleGraphModel.hpp"

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

    scene->setOrientation(Qt::Vertical);

    QWidget window;

    QHBoxLayout *l = new QHBoxLayout(&window);

    QExtBPGraphicsView view(scene);

    l->addWidget(&view);

    QGroupBox *groupBox = new QGroupBox("Orientation");

    QRadioButton *radio1 = new QRadioButton("Vertical");
    QRadioButton *radio2 = new QRadioButton("Horizontal");

    QVBoxLayout *vbl = new QVBoxLayout;
    vbl->addWidget(radio1);
    vbl->addWidget(radio2);
    vbl->addStretch();
    groupBox->setLayout(vbl);

    QObject::connect(radio1, &QRadioButton::clicked, [&scene]() {
        scene->setOrientation(Qt::Vertical);
    });

    QObject::connect(radio2, &QRadioButton::clicked, [&scene]() {
        scene->setOrientation(Qt::Horizontal);
    });

    radio1->setChecked(true);

    l->addWidget(groupBox);

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

    window.setWindowTitle("Graph Orientation Demo");
    window.resize(800, 600);

    // Center window.
    window.move(QApplication::primaryScreen()->availableGeometry().center() - view.rect().center());
    window.showNormal();

    return app.exec();
}
