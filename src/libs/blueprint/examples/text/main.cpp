#include <QExtBlueprint>

#include <QtWidgets/QApplication>

#include "TextDisplayDataModel.hpp"
#include "TextSourceDataModel.hpp"

static std::shared_ptr<QExtBPNodeDelegateModelRegistry> registerDataModels()
{
    auto ret = std::make_shared<QExtBPNodeDelegateModelRegistry>();

    ret->registerModel<TextSourceDataModel>();
    ret->registerModel<TextDisplayDataModel>();

    return ret;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    std::shared_ptr<QExtBPNodeDelegateModelRegistry> registry = registerDataModels();
    QExtBPDataFlowGraphModel dataFlowGraphModel(registry);

    QExtBPDataFlowGraphicsScene scene(dataFlowGraphModel);

    QExtBPGraphicsView view(&scene);

    view.setWindowTitle("Node-based flow editor");
    view.resize(800, 600);
    view.show();

    return app.exec();
}
