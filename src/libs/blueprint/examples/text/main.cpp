#include <QExtBlueprint>

#include <QtWidgets/QApplication>

#include "TextDisplayDataModel.hpp"
#include "TextSourceDataModel.hpp"

static QSharedPointer<QExtBPNodeDelegateModelRegistry> registerDataModels()
{
    auto ret = qextMakeShared<QExtBPNodeDelegateModelRegistry>();

    ret->registerModel<TextSourceDataModel>();
    ret->registerModel<TextDisplayDataModel>();

    return ret;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSharedPointer<QExtBPNodeDelegateModelRegistry> registry = registerDataModels();
    QExtBPDataFlowGraphModel dataFlowGraphModel(registry);

    QExtBPDataFlowGraphicsScene scene(dataFlowGraphModel);

    QExtBPGraphicsView view(&scene);

    view.setWindowTitle("Node-based flow editor");
    view.resize(800, 600);
    view.show();

    return app.exec();
}
