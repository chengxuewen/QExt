#include <QExtBlueprint>

#include <QtGui/QScreen>
#include <QtWidgets/QApplication>

#include "ImageLoaderModel.hpp"
#include "ImageShowModel.hpp"


static QSharedPointer<QExtBPNodeDelegateModelRegistry> registerDataModels()
{
    auto ret = qextMakeShared<QExtBPNodeDelegateModelRegistry>();
    ret->registerModel<ImageShowModel>();

    ret->registerModel<ImageLoaderModel>();

    return ret;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSharedPointer<QExtBPNodeDelegateModelRegistry> registry = registerDataModels();

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
