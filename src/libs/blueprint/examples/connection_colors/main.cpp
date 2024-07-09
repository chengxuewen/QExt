#include <QtWidgets/QApplication>

// #include <QtNodes/ConnectionStyle>
// #include <QtNodes/DataFlowGraphModel>
// #include <QtNodes/DataFlowGraphicsScene>
// #include <QtNodes/GraphicsView>
// #include <QtNodes/NodeData>
// #include <QtNodes/NodeDelegateModelRegistry>
#include <qextBlueprintNode.h>

#include "models.hpp"

//using QtNodes::QExtBPConnectionStyle;
//using QtNodes::QExtBPDataFlowGraphicsScene;
//using QExtBPDataFlowGraphModel;
//using QtNodes::QExtBPGraphicsView;
//using QExtBPNodeDelegateModelRegistry;

static std::shared_ptr<QExtBPNodeDelegateModelRegistry> registerDataModels()
{
    auto ret = std::make_shared<QExtBPNodeDelegateModelRegistry>();

    ret->registerModel<NaiveDataModel>();

    /*
     We could have more models registered.
     All of them become items in the context meny of the scene.

     ret->registerModel<AnotherDataModel>();
     ret->registerModel<OneMoreDataModel>();

   */

    return ret;
}

static void setStyle()
{
    QExtBPConnectionStyle::setConnectionStyle(
        R"(
  {
    "ConnectionStyle": {
      "UseDataDefinedColors": true
    }
  }
  )");
}

//------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    setStyle();

    std::shared_ptr<QExtBPNodeDelegateModelRegistry> registry = registerDataModels();
    QExtBPDataFlowGraphModel dataFlowGraphModel(registry);

    QExtBPDataFlowGraphicsScene scene(dataFlowGraphModel);

    QExtBPGraphicsView view(&scene);

    view.setWindowTitle("Node-based flow editor");
    view.resize(800, 600);
    view.show();

    return app.exec();
}
