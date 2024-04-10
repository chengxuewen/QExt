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
    QVBoxLayout *l = new QVBoxLayout(&mainWidget);

    auto scene = new QExtBlueprintScene(&mainWidget);
    auto view = new QExtBlueprintView(scene);
    l->addWidget(view);
    l->setContentsMargins(0, 0, 0, 0);
    l->setSpacing(0);

    mainWidget.setWindowTitle("Simplest blueprint");
    mainWidget.resize(800, 600);
    // Center window.
    mainWidget.move(QApplication::primaryScreen()->availableGeometry().center()
                    - mainWidget.rect().center());
    mainWidget.showNormal();
    return app.exec();
}
