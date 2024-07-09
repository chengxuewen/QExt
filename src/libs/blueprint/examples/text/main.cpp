// #include <QtNodes/DataFlowGraphModel>
// #include <QtNodes/DataFlowGraphicsScene>
// #include <QtNodes/GraphicsView>
// #include <QtNodes/NodeData>
// #include <QtNodes/NodeDelegateModelRegistry>
#include <qextBlueprintNode.h>

#include <QtWidgets/QApplication>

#include "TextDisplayDataModel.hpp"
#include "TextSourceDataModel.hpp"

//using QtNodes::QExtBPDataFlowGraphicsScene;
//using QExtBPDataFlowGraphModel;
//using QtNodes::QExtBPGraphicsView;
//using QExtBPNodeDelegateModelRegistry;

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
