#include <QApplication>

#include "mycontroller.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MyController *controller = new MyController();
    controller->show();

    int ret = app.exec();
    return ret;
}
