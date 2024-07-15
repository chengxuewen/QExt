#include <QExtBlueprint>

#include <QAction>
#include <QScreen>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>

#include "DataFlowModel.hpp"
#include "DelegateNodeModel.hpp"


static QSharedPointer<QExtBPNodeDelegateModelRegistry> registerDataModels()
{
    auto ret = qextMakeShared<QExtBPNodeDelegateModelRegistry>();

    ret->registerModel<SimpleDataModel>();

    return ret;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DataFlowModel graphModel(registerDataModels());

    // Initialize and connect two nodes.
    {
        QExtBPTypes::NodeId id1 = graphModel.addNode(SimpleNodeData().type().id);
        graphModel.setNodeData(id1, QExtBPTypes::NodeRole_Position, QPointF(0, 0));

        QExtBPTypes::NodeId id2 = graphModel.addNode(SimpleNodeData().type().id);
        graphModel.setNodeData(id2, QExtBPTypes::NodeRole_Position, QPointF(300, 300));

        graphModel.addConnection(QExtBPTypes::ConnectionId{id1, 0, id2, 0});
    }

    auto scene = new QExtBPDataFlowGraphicsScene(graphModel);

    QWidget window;

    QHBoxLayout *l = new QHBoxLayout(&window);

    QExtBPGraphicsView view(scene);

    l->addWidget(&view);

    QGroupBox *groupBox = new QGroupBox("Options");

    QCheckBox *cb1 = new QCheckBox("Nodes are locked");
    QCheckBox *cb2 = new QCheckBox("Connections detachable");
    cb2->setChecked(true);

    QVBoxLayout *vbl = new QVBoxLayout;
    vbl->addWidget(cb1);
    vbl->addWidget(cb2);
    vbl->addStretch();
    groupBox->setLayout(vbl);

    QObject::connect(cb1, &QCheckBox::stateChanged, [&graphModel](int state) {
        graphModel.setNodesLocked(state == Qt::Checked);
    });

    QObject::connect(cb2, &QCheckBox::stateChanged, [&graphModel](int state) {
        graphModel.setDetachPossible(state == Qt::Checked);
    });

    l->addWidget(groupBox);

    window.setWindowTitle("Locked Nodes and Connections");
    window.resize(800, 600);

    // Center window.
    window.move(QApplication::primaryScreen()->availableGeometry().center() - view.rect().center());
    window.showNormal();

    return app.exec();
}
