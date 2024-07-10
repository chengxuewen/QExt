#include <QExtBlueprint>

#include <QtGui/QScreen>
#include <QtWidgets/QApplication>

#include "ImageLoaderModel.hpp"
#include "ImageShowModel.hpp"


static std::shared_ptr<QExtBPNodeDelegateModelRegistry> registerDataModels()
{
    auto ret = std::make_shared<QExtBPNodeDelegateModelRegistry>();
    ret->registerModel<ImageShowModel>();

    ret->registerModel<ImageLoaderModel>();

    return ret;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    std::shared_ptr<QExtBPNodeDelegateModelRegistry> registry = registerDataModels();

    QExtBPDataFlowGraphModel dataFlowGraphModel(registry);

    QExtBPDataFlowGraphicsScene scene(dataFlowGraphModel);

    QExtBPGraphicsView view(&scene);

    view.setWindowTitle("Data Flow: Resizable Images");
    view.resize(800, 600);
    // Center window.
    view.move(QApplication::primaryScreen()->availableGeometry().center() - view.rect().center());
    view.show();

    return app.exec();
}
