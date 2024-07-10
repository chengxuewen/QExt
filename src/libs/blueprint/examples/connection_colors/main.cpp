#include <QtWidgets/QApplication>

#include <QExtBlueprint>

#include "models.hpp"


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
