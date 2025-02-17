#include <QExtBlueprint>

#include <QtGui/QScreen>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QVBoxLayout>

#include <QtGui/QScreen>

#include "AdditionModel.hpp"
#include "DivisionModel.hpp"
#include "MultiplicationModel.hpp"
#include "NumberDisplayDataModel.hpp"
#include "NumberSourceDataModel.hpp"
#include "SubtractionModel.hpp"

static QExtSharedPointer<QExtBPNodeDelegateModelRegistry> registerDataModels()
{
    auto ret = qextMakeShared<QExtBPNodeDelegateModelRegistry>();
    ret->registerModel<NumberSourceDataModel>("Sources");

    ret->registerModel<NumberDisplayDataModel>("Displays");

    ret->registerModel<AdditionModel>("Operators");

    ret->registerModel<SubtractionModel>("Operators");

    ret->registerModel<MultiplicationModel>("Operators");

    ret->registerModel<DivisionModel>("Operators");

    return ret;
}

static void setStyle()
{
    QExtBPConnectionStyle::setConnectionStyle(
        R"(
  {
    "ConnectionStyle": {
      "ConstructionColor": "gray",
      "NormalColor": "black",
      "SelectedColor": "gray",
      "SelectedHaloColor": "deepskyblue",
      "HoveredColor": "deepskyblue",

      "LineWidth": 3.0,
      "ConstructionLineWidth": 2.0,
      "PointDiameter": 10.0,

      "UseDataDefinedColors": true
    }
  }
  )");
}

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    fprintf(stderr, "%s\n", msg.toLatin1().data());
}
int main(int argc, char *argv[])
{
    qInstallMessageHandler(&messageHandler);
    QApplication app(argc, argv);

    setStyle();

    QExtSharedPointer<QExtBPNodeDelegateModelRegistry> registry = registerDataModels();

    QWidget mainWidget;

    auto menuBar = new QMenuBar();
    QMenu *menu = menuBar->addMenu("File");
    auto saveAction = menu->addAction("Save Scene");
    auto loadAction = menu->addAction("Load Scene");

    QVBoxLayout *l = new QVBoxLayout(&mainWidget);

    QExtBPDataFlowGraphModel dataFlowGraphModel(registry);

    l->addWidget(menuBar);
    auto scene = new QExtBPDataFlowGraphicsScene(dataFlowGraphModel, &mainWidget);

    auto view = new QExtBPGraphicsView(scene);
    l->addWidget(view);
    l->setContentsMargins(0, 0, 0, 0);
    l->setSpacing(0);

    QObject::connect(saveAction, &QAction::triggered, scene, &QExtBPDataFlowGraphicsScene::save);

    QObject::connect(loadAction, &QAction::triggered, scene, &QExtBPDataFlowGraphicsScene::load);

    QObject::connect(scene, &QExtBPDataFlowGraphicsScene::sceneLoaded, view, &QExtBPGraphicsView::centerScene);

    mainWidget.setWindowTitle("Data Flow: simplest calculator");
    mainWidget.resize(800, 600);
    // Center window.
    mainWidget.move(QApplication::primaryScreen()->availableGeometry().center()
                    - mainWidget.rect().center());
    mainWidget.showNormal();

    return app.exec();
}
