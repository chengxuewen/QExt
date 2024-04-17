#include <QApplication>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QScreen>
#include <QScreen>

#include <qextBlueprintScene.h>
#include <qextBlueprintView.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget mainWidget;
    QVBoxLayout *layout = new QVBoxLayout(&mainWidget);

    QExtBlueprintScene *scene = new QExtBlueprintScene(&mainWidget);
    QExtBlueprintView *view = new QExtBlueprintView(scene);
    layout->addWidget(view);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    mainWidget.setWindowTitle("Simplest blueprint");
    mainWidget.resize(800, 600);
    mainWidget.showNormal();
    return app.exec();
}
